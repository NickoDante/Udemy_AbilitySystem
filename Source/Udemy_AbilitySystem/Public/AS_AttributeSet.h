// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AS_AttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_ABILITYSYSTEM_API UAS_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UAS_AttributeSet();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData Health;

protected:

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
};
