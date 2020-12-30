// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_GATargetActorGroundSelect.h"

// Not sure if is the Begin Play
void AAS_GATargetActorGroundSelect::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

// Not sure if is the Tick...
bool AAS_GATargetActorGroundSelect::IsConfirmTargetingAllowed()
{
	// Get the point where the player is looking at.
	FVector ViewPoint = FVector::ZeroVector;
	FRotator ViewRotation = FRotator::ZeroRotator;

	MasterPC->GetPlayerViewPoint(ViewPoint, ViewRotation);
	
	// Start to create a line trace to know where occurs the impact from the player view to the world.
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;

	// Add the Owner Pawn to the ignored list
	APawn* MasterPawn = MasterPC->GetPawn();
	if (IsValid(MasterPawn))
	{
		QueryParams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}

	// Trace the line to know if exist impact.
	FVector LookAtPoint = FVector::ZeroVector;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPoint, ViewPoint + ViewRotation.Vector() * 10000.0f, ECC_Visibility, QueryParams);
	if (bHit)
	{
		LookAtPoint = HitResult.ImpactPoint;
	}
}
