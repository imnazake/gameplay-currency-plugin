// Copyright Neoxyne. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CurrencyData.generated.h"

/**
 * FGameplayCurrencyData
 */
USTRUCT(BlueprintType)
struct FCurrencyData
{
	GENERATED_BODY()

public:

	FCurrencyData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	int32 CopperCoins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	int32 SilverCoins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	int32 GoldCoins;

	FORCEINLINE bool IsGreaterThanZero() const
	{
		return (CopperCoins > 0) && (SilverCoins > 0) && (GoldCoins > 0);
	}

	FORCEINLINE bool operator == (const FCurrencyData& Other) const
	{
		return Other.CopperCoins == CopperCoins && Other.SilverCoins == SilverCoins && Other.GoldCoins == GoldCoins;
	}

	FORCEINLINE bool operator != (const FCurrencyData& Other) const
	{
		return !(operator==(Other));
	}

	static const FCurrencyData ZeroCurrency;
	
};
