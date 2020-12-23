// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AS_GameplayAbilityBase.h"

FGameplayAbilityInfo UAS_GameplayAbilityBase::GetAbilityInfo()
{
	UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();

	if (CooldownEffect && CostEffect)
	{
		// Get the cooldown duration value.
		float CooldownDuration = 0.0f;
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CooldownDuration);

		// Get the cost value.
		float Cost = 0.0f;
		EAbilityCostType CostType;
		if (CostEffect->Modifiers.Num() > 0)
		{
			FGameplayModifierInfo EffectInfo = CostEffect->Modifiers[0];
			EffectInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);

			// Get the cost type BY ITS NAME
			FGameplayAttribute CostAttribute = EffectInfo.Attribute;
			FString AttributeName = CostAttribute.AttributeName;
			
			if (AttributeName == "Health")
			{
				CostType = EAbilityCostType::Health;
			}
			else if (AttributeName == "Mana")
			{
				CostType = EAbilityCostType::Mana;
			}
			else if (AttributeName == "Strength")
			{
				CostType = EAbilityCostType::Strength;
			}
		}

		return FGameplayAbilityInfo(CooldownDuration, Cost, CostType, UIMaterial, GetClass());
	}

	return FGameplayAbilityInfo();
}
