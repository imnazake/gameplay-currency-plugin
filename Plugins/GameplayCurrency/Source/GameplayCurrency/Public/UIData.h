// Copyright Neoxyne. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UIData.generated.h"

class USoundBase;

/**
 * UUIData
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew, Const)
class GAMEPLAYCURRENCY_API UUIData : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Text")
	FText CopperCoinDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Text")
	FText SilverCoinDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Text")
	FText GoldCoinDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Brush")
	FSlateBrush CopperCoinDisplayImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Brush")
	FSlateBrush SilverCoinDisplayImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Brush")
	FSlateBrush GoldCoinDisplayImage;

	/** Sound to play whenever coins have been added to the balance. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Sounds")
	USoundBase* AddedCurrencySound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Sounds")
	/** Sound to play whenever coins have been consumed from the balance. */
	USoundBase* ConsumedCurrencySound;
	
};
