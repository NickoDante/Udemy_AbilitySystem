// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_CharacterBase.h"
#include "AS_AttributeSet.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "BrainComponent.h"

// Sets default values
AAS_CharacterBase::AAS_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSetBaseComponent = CreateDefaultSubobject<UAS_AttributeSet>("AttributeSetComponent");

	bIsDead = false;
	TeamID = 255;
}

// Called when the game starts or when spawned
void AAS_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	AttributeSetBaseComponent->OnHealthChangeDelegate.AddDynamic(this, &AAS_CharacterBase::OnHealthChange);

	AutoDeterminTeamIDbyControllerType();
}

// Called every frame
void AAS_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAS_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AAS_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAS_CharacterBase::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
{
	if (IsValid(AbilitySystemComponent))
	{
		if (HasAuthority() && AbilityToAquire)
		{
			FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
			SpecDef.Ability = AbilityToAquire;
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(SpecDef, 1);
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}

		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AAS_CharacterBase::OnHealthChange(float Health, float MaxHealth)
{
	if (Health <= 0.0f && !bIsDead)
	{
		bIsDead = true;
		Dead();
		BP_Die();
	}

	BP_OnHealthChange(Health, MaxHealth);
}

void AAS_CharacterBase::AutoDeterminTeamIDbyControllerType()
{
	if (GetController() && GetController()->IsPlayerController())
	{
		TeamID = 0;
	}
}

bool AAS_CharacterBase::IsOtherHostile(AAS_CharacterBase* OtherCharacter) const
{
	return TeamID != OtherCharacter->GetTeamID();
}

void AAS_CharacterBase::Dead()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->DisableInput(PC);
	}

	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->StopLogic("Dead");
	}
}

