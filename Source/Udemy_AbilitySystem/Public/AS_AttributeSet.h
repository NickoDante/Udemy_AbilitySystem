// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AS_AttributeSet.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeSignature, float, Health, float, MaxHealth);

UCLASS()
class UDEMY_ABILITYSYSTEM_API UAS_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UAS_AttributeSet();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData MaxStrength;

public:

	FOnHealthChangeSignature OnHealthChangeDelegate;
	FOnHealthChangeSignature OnManaChangeDelegate;
	FOnHealthChangeSignature OnStrengthChangeDelegate;

protected:

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
};
