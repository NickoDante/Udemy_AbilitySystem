// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AS_AbilityTypes.h"
#include "AS_PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_ABILITYSYSTEM_API AAS_PlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public: 

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerControllerBase")
	void AddAbilityToUI(FAS_GameplayAbilityInfo AbilityInfo);
};
