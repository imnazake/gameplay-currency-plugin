// Copyright Neoxyne. All Rights Reserved.

#include "CurrencyComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

UCurrencyComponent::UCurrencyComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

	bAddStartupCurrencyOnBeginPlay = false;
	Balance = FCurrencyData::ZeroCurrency;
}

void UCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bAddStartupCurrencyOnBeginPlay)
	{
		AddStartupCurrency();
	}
}

void UCurrencyComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Balance);
}

FBalanceEvent& UCurrencyComponent::OnBalanceChangedDelegate()
{
	return OnBalanceChanged;
}

FCurrencyData& UCurrencyComponent::GetBalance()
{
	return Balance;
}

int32 UCurrencyComponent::GetBalanceValue() const
{
	const int32 Value = Balance.CopperCoins + (Balance.SilverCoins * 100) + (Balance.GoldCoins * 10000);
	return Value;	
}

int32 UCurrencyComponent::GetValueFromCurrency(const FCurrencyData& Currency) const
{
	const int32 Coins = Currency.CopperCoins + (Currency.SilverCoins * 100) + (Currency.GoldCoins * 10000);
	return Coins;	
}

FCurrencyData UCurrencyComponent::GetCurrencyFromValue(const int32 Value) const
{
	FCurrencyData Currency;

	double Remainder01 = 0.0f;
	Currency.GoldCoins = UKismetMathLibrary::FMod(Value, 10000.0f, Remainder01);
	
	double Remainder02 = 0.0f;
	Currency.SilverCoins = UKismetMathLibrary::FMod(Remainder01, 100.0f, Remainder02);
	
	Currency.CopperCoins = FMath::TruncToInt32(Remainder02);
	return Currency;
}

bool UCurrencyComponent::CheckCost(const FCurrencyData& Cost) const
{
	const int32 BalanceValue = GetBalanceValue();
	const int32 CostValue = GetValueFromCurrency(Cost);

	if (BalanceValue - CostValue >= 0)
	{
		return true;
	}

	return false;
}

UUIData* UCurrencyComponent::GetUIData() const
{
	return UIData;
}

void UCurrencyComponent::AddStartupCurrency()
{
	if (!StartupCurrency.IsGreaterThanZero())
	{
		return;
	}

	AddCurrency(StartupCurrency);
}

void UCurrencyComponent::AddCurrency(const FCurrencyData& Value)
{
	if (!Value.IsGreaterThanZero())
	{
		return;
	}
	
	const FCurrencyData CachedBalance = Balance;
	const int32 ValueOfCoinsToAdd = GetValueFromCurrency(Value);
	const int32 CurrentBalance = GetBalanceValue();
	const int32 NewValue = CurrentBalance + ValueOfCoinsToAdd;
	
	Balance = GetCurrencyFromValue(NewValue);
	OnRep_Balance(CachedBalance);
}

void UCurrencyComponent::Server_AddCurrency_Implementation(const FCurrencyData& Value)
{
	AddCurrency(Value);
}

bool UCurrencyComponent::Server_AddCurrency_Validate(const FCurrencyData& Value)
{
	return Value.IsGreaterThanZero();	
}

void UCurrencyComponent::RequestAddCurrency(const FCurrencyData& Value)
{
	if (GetOwner()->HasAuthority())
	{
		AddCurrency(Value);
	}
	else
	{
		Server_AddCurrency(Value);
	}
}

void UCurrencyComponent::RemoveCurrency(const FCurrencyData& Value)
{
	if (!Value.IsGreaterThanZero())
	{
		return;
	}
	
	const FCurrencyData CachedBalance = Balance;
	const int32 ValueOfCoinsToRemove = GetValueFromCurrency(Value);
	const int32 BalanceValue = GetBalanceValue();

	if (BalanceValue - ValueOfCoinsToRemove >= 0)
	{
		Balance = GetCurrencyFromValue(BalanceValue - ValueOfCoinsToRemove);
		OnRep_Balance(CachedBalance);
	}
	else
	{
		Balance = FCurrencyData::ZeroCurrency;
		OnRep_Balance(CachedBalance);
	}
}

void UCurrencyComponent::Server_RemoveCurrency_Implementation(const FCurrencyData& Value)
{
	RemoveCurrency(Value);
}

bool UCurrencyComponent::Server_RemoveCurrency_Validate(const FCurrencyData& Value)
{
	return Value.IsGreaterThanZero();
}

void UCurrencyComponent::RequestRemoveCurrency(const FCurrencyData& Value)
{
	if (GetOwner()->HasAuthority())
	{
		RemoveCurrency(Value);
	}
	else
	{
		Server_RemoveCurrency(Value);
	}
}

void UCurrencyComponent::OnRep_Balance(const FCurrencyData& OldBalance)
{
	const int32 OldBalanceValue = GetValueFromCurrency(OldBalance);
	const int32 CurrentBalanceValue = GetBalanceValue();
	
	NotifyBalanceChanged(CurrentBalanceValue - OldBalanceValue);
}

void UCurrencyComponent::NotifyBalanceChanged(int32 Delta)
{
	OnBalanceChanged.Broadcast(Balance, Delta);
	K2_OnBalanceChanged(Balance, Delta);
}
