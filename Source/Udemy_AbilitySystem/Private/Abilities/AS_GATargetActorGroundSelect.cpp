// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AS_GATargetActorGroundSelect.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

AAS_GATargetActorGroundSelect::AAS_GATargetActorGroundSelect()
{
	PrimaryActorTick.bCanEverTick = true;
	Radius = 200.0f;
}

void AAS_GATargetActorGroundSelect::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AAS_GATargetActorGroundSelect::ConfirmTargetingAndContinue()
{
	// Get the point where the player is looking at.
	FVector ViewLocation = FVector::ZeroVector;
	GetPlayerLookingPoint(ViewLocation);

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
		for (int32 i = 0; i<Overlaps.Num(); i++)
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

void AAS_GATargetActorGroundSelect::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// Debugging the sphere behavior.
	FVector LookPoint;
	GetPlayerLookingPoint(LookPoint);
	DrawDebugSphere(GetWorld(), LookPoint, Radius, 32, FColor::Red, false, -1.0, 0, 5.0f);
}

bool AAS_GATargetActorGroundSelect::GetPlayerLookingPoint(FVector& OutViewpoint)
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
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPoint, ViewPoint + ViewRotation.Vector() * 10000.0f, ECC_Visibility, QueryParams);
	if (bHit)
	{
		OutViewpoint = HitResult.ImpactPoint;
	}
	else
	{
		OutViewpoint = FVector::ZeroVector;
	}

	return bHit;
}
