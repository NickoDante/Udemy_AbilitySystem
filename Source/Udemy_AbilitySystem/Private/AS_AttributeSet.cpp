// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "AS_CharacterBase.h"

UAS_AttributeSet::UAS_AttributeSet()
	: Health(200.0f),
	MaxHealth(200.0f),
	Mana(100.0f),
	MaxMana(100.0f),
	Strength(250.0f),
	MaxStrength(250.0f)
{

}

void UAS_AttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	// If the value that has been affected was the Health.
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAS_AttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UAS_AttributeSet, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.0f, MaxHealth.GetBaseValue()));
		OnHealthChangeDelegate.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
		
		AAS_CharacterBase* CharacterOwner = Cast<AAS_CharacterBase>(GetOwningActor());
		if (Health.GetCurrentValue() == MaxHealth.GetCurrentValue())
		{
			if (CharacterOwner)
			{
				CharacterOwner->AddGameplayTag(CharacterOwner->FullHealthTag);
			}
		}
		else
		{
			if (CharacterOwner)
			{
				CharacterOwner->RemoveGameplayTag(CharacterOwner->FullHealthTag);
			}
		}
	}

	// If the value that has been affected was the Health.
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAS_AttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UAS_AttributeSet, Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.0f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.0f, MaxMana.GetBaseValue()));
		OnManaChangeDelegate.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}

	// If the value that has been affected was the Health.
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAS_AttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UAS_AttributeSet, Strength)))
	{
		Strength.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(), 0.0f, MaxStrength.GetCurrentValue()));
		Strength.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(), 0.0f, MaxStrength.GetBaseValue()));
		OnStrengthChangeDelegate.Broadcast(Strength.GetCurrentValue(), MaxStrength.GetCurrentValue());
	}
}
