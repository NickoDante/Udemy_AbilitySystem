// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

UAS_AttributeSet::UAS_AttributeSet()
	: Health(200.0f),
	MaxHealth(200.0f)
{

}

void UAS_AttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	// If the value that has been affected was the Health.
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAS_AttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UAS_AttributeSet, Health)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ouch, I took some damage, now my Health is: %f"), Health.GetCurrentValue());
		OnHealthChangeDelegate.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	}
}
