// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_AbilityTypes.h"

FGameplayAbilityInfo::FGameplayAbilityInfo()
	:CooldownDuration(0.0f),
	Cost(0.0f),
	CostType(EAbilityCostType::Mana),
	UIMaterial(nullptr),
	AbilityClass(nullptr)
{

}

FGameplayAbilityInfo::FGameplayAbilityInfo(float InCoolDuration, float InCost, EAbilityCostType InCostType, UMaterialInstance* InUIMaterial, TSubclassOf<UAS_GameplayAbilityBase> InAbilityClass)
	:CooldownDuration(InCoolDuration),
	Cost(InCost),
	CostType(InCostType),
	UIMaterial(InUIMaterial),
	AbilityClass(InAbilityClass)
{

}
