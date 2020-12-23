// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_CharacterBase.h"
#include "AS_AttributeSet.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Abilities/AS_GameplayAbilityBase.h"
#include "AS_PlayerControllerBase.h"

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
	AttributeSetBaseComponent->OnManaChangeDelegate.AddDynamic(this, &AAS_CharacterBase::OnManaChange);
	AttributeSetBaseComponent->OnStrengthChangeDelegate.AddDynamic(this, &AAS_CharacterBase::OnStrengthChange);

	AutoDeterminTeamIDbyControllerType();
	AddGameplayTag(FullHealthTag);
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

void AAS_CharacterBase::AquireAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAquire)
{
	for (TSubclassOf<UGameplayAbility> NewAbility : AbilitiesToAquire)
	{
		AquireAbility(NewAbility);

		// Then, check if is our own Gameplay Ability to include it to the UI
		if (NewAbility->IsChildOf(UAS_GameplayAbilityBase::StaticClass()))
		{
			// Get the TsubclassOf
			TSubclassOf<UAS_GameplayAbilityBase> AbilityBaseClass = *NewAbility;
			if (AbilityBaseClass != nullptr)
			{
				AddAbilityToUI(AbilityBaseClass);
			}
		}
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

void AAS_CharacterBase::OnManaChange(float Mana, float MaxMana)
{
	BP_OnManaChange(Mana, MaxMana);
}

void AAS_CharacterBase::OnStrengthChange(float Strength, float MaxStrength)
{
	BP_OnStrengthChange(Strength, MaxStrength);
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
	DisableInputControl();
}

void AAS_CharacterBase::AddGameplayTag(FGameplayTag TagToAdd)
{
	GetAbilitySystemComponent()->AddLooseGameplayTag(TagToAdd);
	GetAbilitySystemComponent()->SetTagMapCount(TagToAdd, 1);
}

void AAS_CharacterBase::RemoveGameplayTag(FGameplayTag TagToRemove)
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(TagToRemove);
}

void AAS_CharacterBase::DisableInputControl()
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

void AAS_CharacterBase::EnableInputControl()
{
	if (bIsDead)
	{
		return;
	}

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->EnableInput(PC);
	}

	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->RestartLogic();
	}
}

void AAS_CharacterBase::HitStun(const float StunDuration)
{
	DisableInputControl();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Stun, this, &AAS_CharacterBase::EnableInputControl, StunDuration);
}

void AAS_CharacterBase::AddAbilityToUI(TSubclassOf<UAS_GameplayAbilityBase> AbilityToAdd)
{
	AAS_PlayerControllerBase* PlayerControllerBase = Cast<AAS_PlayerControllerBase>(GetController());
	if (PlayerControllerBase)
	{
		UAS_GameplayAbilityBase* AbilityInstance = AbilityToAdd->GetDefaultObject<UAS_GameplayAbilityBase>();
		if (AbilityInstance)
		{
			// Get the info of this Gameplay Ability & ad to the UI on the player controller.
			FAS_GameplayAbilityInfo AbilityInfo = AbilityInstance->GetAbilityInfo();
			PlayerControllerBase->AddAbilityToUI(AbilityInfo);
		}
	}
}

