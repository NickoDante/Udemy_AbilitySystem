// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_AbilityTypes.h"

FAS_GameplayAbilityInfo::FAS_GameplayAbilityInfo()
	:CooldownDuration(0.0f),
	Cost(0.0f),
	CostType(EAS_AbilityCostType::Mana),
	UIMaterial(nullptr),
	AbilityClass(nullptr)
{

}

FAS_GameplayAbilityInfo::FAS_GameplayAbilityInfo(float InCoolDuration, float InCost, EAS_AbilityCostType InCostType, UMaterialInstance* InUIMaterial, TSubclassOf<UAS_GameplayAbilityBase> InAbilityClass)
	:CooldownDuration(InCoolDuration),
	Cost(InCost),
	CostType(InCostType),
	UIMaterial(InUIMaterial),
	AbilityClass(InAbilityClass)
{

}
