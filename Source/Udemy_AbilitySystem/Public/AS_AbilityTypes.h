// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AS_AbilityTypes.generated.h"

class UAS_GameplayAbilityBase;

UENUM(BlueprintType)
enum class EAbilityCostType : uint8 
{
	Health,
	Mana,
	Strength
};

USTRUCT(BlueprintType)
struct FGameplayAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityInfo")
	float CooldownDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityInfo")
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityInfo")
	EAbilityCostType CostType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityInfo")
	UMaterialInstance* UIMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityInfo")
	TSubclassOf<UAS_GameplayAbilityBase> AbilityClass;

	FGameplayAbilityInfo();
	FGameplayAbilityInfo(float InCoolDuration, float InCost, EAbilityCostType InCostType, UMaterialInstance* InUIMaterial, TSubclassOf<UAS_GameplayAbilityBase> InAbilityClass);
};