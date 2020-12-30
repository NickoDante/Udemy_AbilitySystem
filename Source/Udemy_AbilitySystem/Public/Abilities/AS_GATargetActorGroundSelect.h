// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "AS_GATargetActorGroundSelect.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_ABILITYSYSTEM_API AAS_GATargetActorGroundSelect : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Select")
	float Radius;

public: 

	/** Initialize and begin targeting logic  */
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Ground Select")
	bool GetPlayerLookingPoint(FVector& OutViewpoint);
};
