// Copyright Neoxyne. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CurrencyData.h"
#include "Components/ActorComponent.h"
#include "CurrencyComponent.generated.h"

class UUIData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBalanceEvent, /*NewBalance*/ FCurrencyData, NewBalance, /*Delta*/ int32, Delta);

/**
 * UCurrencyComponent
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup = ("Gameplay"))
class GAMEPLAYCURRENCY_API UCurrencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCurrencyComponent();

	//~ UActorComponent Interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
	//~ UActorComponent Interface

	FBalanceEvent& OnBalanceChangedDelegate();

	/** Returns the currenct currency balance. */
	UFUNCTION(BlueprintPure, Category = "GameplayCurrency")
	FCurrencyData& GetBalance();

	/** Returns the current balance total value. */
	UFUNCTION(BlueprintPure, Category = "GameplayCurrency")
	int32 GetBalanceValue() const;

	/** Returns the value of the specified currency coins. */
	UFUNCTION(BlueprintPure, Category = "GameplayCurrency")
	int32 GetValueFromCurrency(const FCurrencyData& Currency) const;

	/** Returns the currency data from the specified total currency coins value. */
	UFUNCTION(BlueprintPure, Category = "GameplayCurrency")
	FCurrencyData GetCurrencyFromValue(const int32 Value) const;

	/** Returns true, if we can pay for the specified cost with our currency balance. */
	UFUNCTION(BlueprintPure, Category = "GameplayCurrency")
	bool CheckCost(const FCurrencyData& Cost) const;

	/** Returns the user interface data object for this component. */
	UFUNCTION(BlueprintPure, Category = "GameplayCurrency")
	UUIData* GetUIData() const;

	/**
	 * Called when the currency balance changes.
	 * @note Delta = 0 : means the coins balance did not change
	 * @note Delta > 0 : means coins were added to the balance
	 * @note Delta < 0 : means coins were removed from the balance
	 *
	 * @note Call GetCurrencyFromValue() and pass in the delta to convert the change in gold, silver, copper.
	 * (Maybe some games need to display the amount of coins add or remove at some point)
	 */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Balance Changed"), Category = "GameplayCurrency")
	void K2_OnBalanceChanged(const FCurrencyData& NewBalance, const int32 Delta);

	/** Adds start up currency to the player currency balance. */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "GameplayCurrency")
	void AddStartupCurrency();

	/** Adds the specified currency value to the currency balance. */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "GameplayCurrency")
	void AddCurrency(const FCurrencyData& Value);

	/** Sends a request to the server to add the specified currency value to the currency balance. */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AddCurrency(const FCurrencyData& Value);

	/** Sends a request to the server to add the specified currency value to the currency balance. */
	UFUNCTION(BlueprintCallable, Category = "GameplayCurrency")
	void RequestAddCurrency(const FCurrencyData& Value);

	/** Removes the specified currency value from the currency balance. */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "GameplayCurrency")
	void RemoveCurrency(const FCurrencyData& Value);

	/** Sends a request to the server to remove the specified currency value from the currency balance. */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RemoveCurrency(const FCurrencyData& Value);

	/** Sends a request to the server to remove the specified currency value from the currency balance. */
	UFUNCTION(BlueprintCallable, Category = "GameplayCurrency")
	void RequestRemoveCurrency(const FCurrencyData& Value);

protected:

	/** Currency balance to give to the player on begin play or whenever AddStartupCurrency() is called. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayCurrency")
	FCurrencyData StartupCurrency;

	/** Whether we should add startup currency balance on begin play. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayCurrency")
	uint8 bAddStartupCurrencyOnBeginPlay : 1;

	/** Contains data that is used to display currency on the user-interface. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayCurrency")
	UUIData* UIData;

	UFUNCTION()
	virtual void OnRep_Balance(const FCurrencyData& OldBalance);

	/** Notifies listeners that the balance has changed. */
	void NotifyBalanceChanged(int32 Delta);

private:

	/** Delegate that gets called whenever the currency balance changes. */
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FBalanceEvent OnBalanceChanged;

	/** Currently owned currency balance. */
	UPROPERTY(ReplicatedUsing = OnRep_Balance, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "GameplayCurrency")
	FCurrencyData Balance;
	
};
