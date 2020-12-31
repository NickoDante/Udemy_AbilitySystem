// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GATargetActorFireBlastAround.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

AGATargetActorFireBlastAround::AGATargetActorFireBlastAround()
{
	Radius = 200.0f;
}

void AGATargetActorFireBlastAround::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AGATargetActorFireBlastAround::ConfirmTargetingAndContinue()
{
	// Get the point where the player is.
	APawn* OwnerPawn = MasterPC->GetPawn();
	if (!IsValid(OwnerPawn))
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
		return;
	}

	FVector ViewLocation = OwnerPawn->GetActorLocation();

	// Start to configure the overlaps rules with a sphere
	TArray<FOverlapResult> Overlaps;
	TArray<TWeakObjectPtr<AActor>> OverlappedActors;
	bool bTraceComplex = false;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.bTraceComplex = bTraceComplex;
	CollisionQueryParams.bReturnPhysicalMaterial = false;

	// Add the Owner Pawn to the ignored list
	APawn* MasterPawn = MasterPC->GetPawn();
	if (IsValid(MasterPawn))
	{
		CollisionQueryParams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}

	// Create the Overlap Object with a Sphere and the configuration above.
	bool bIsOverlap = GetWorld()->OverlapMultiByObjectType(Overlaps,
		ViewLocation,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECC_Pawn),
		FCollisionShape::MakeSphere(Radius),
		CollisionQueryParams);

	if (bIsOverlap)
	{
		// If is true, check if every actor overlapped is a pawn to add it to an array.
		for (int32 i = 0; i < Overlaps.Num(); i++)
		{
			APawn* PawnOverlapped = Cast<APawn>(Overlaps[i].GetActor());
			if (IsValid(PawnOverlapped) && !OverlappedActors.Contains(PawnOverlapped))
			{
				OverlappedActors.Add(PawnOverlapped);
			}
		}
	}

	// If exist more than 1 overlapped actor, create the Target data to be sended to the broadcast (Check the parent function purpose)
	if (OverlappedActors.Num() > 0)
	{
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlappedActors);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else
	{
		// If not, Return empty data,
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
	}
}
