// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AS_AbilityTypes.h"
#include "AS_GameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_ABILITYSYSTEM_API UAS_GameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityBase")
	UMaterialInstance* UIMaterial;

public: 

	UFUNCTION(BlueprintCallable, Category = "AbilityBase")
	FAS_GameplayAbilityInfo GetAbilityInfo();
	
};