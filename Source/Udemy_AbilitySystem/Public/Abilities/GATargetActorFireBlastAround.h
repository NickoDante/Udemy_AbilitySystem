// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorFireBlastAround.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_ABILITYSYSTEM_API AGATargetActorFireBlastAround : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Blast Around", meta = (ExposeOnSpawn = true))
	float Radius;

public:

	AGATargetActorFireBlastAround();

	/** Initialize and begin targeting logic  */
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;
};
