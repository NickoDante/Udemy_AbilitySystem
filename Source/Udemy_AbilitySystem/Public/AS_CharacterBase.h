// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "AS_AbilityTypes.h"
#include "AS_CharacterBase.generated.h"

class UAS_AttributeSet;
class UAS_GameplayAbilityBase;

UCLASS()
class UDEMY_ABILITYSYSTEM_API AAS_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAS_CharacterBase();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	UAS_AttributeSet* AttributeSetBaseComponent;

protected:

	bool bIsDead;

	uint8 TeamID;

	FTimerHandle TimerHandle_Stun;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterBase")
	FGameplayTag FullHealthTag;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void AquireAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAquire);

	UFUNCTION()
	void OnHealthChange(float Health, float MaxHealth);

	UFUNCTION()
	void OnManaChange(float Mana, float MaxMana);

	UFUNCTION()
	void OnStrengthChange(float Strength, float MaxStrength);

	void AutoDeterminTeamIDbyControllerType();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	bool IsOtherHostile(AAS_CharacterBase* OtherCharacter) const;

	uint8 GetTeamID() const { return TeamID; };

	void Dead();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void AddGameplayTag(FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void RemoveGameplayTag(FGameplayTag TagToRemove);

	UFUNCTION(BlueprintCallable)
	void DisableInputControl();

	UFUNCTION(BlueprintCallable)
	void EnableInputControl();

	UFUNCTION(BlueprintCallable)
	void HitStun(const float StunDuration);

	void AddAbilityToUI(TSubclassOf<UAS_GameplayAbilityBase> AbilityToAdd);

public:

	UFUNCTION(BlueprintImplementableEvent/*, meta = (DisplayName = "OnHealthChange")*/)
	void BP_OnHealthChange(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent/*, meta = (DisplayName = "OnHealthChange")*/)
	void BP_OnManaChange(float Mana, float MaxMana);

	UFUNCTION(BlueprintImplementableEvent/*, meta = (DisplayName = "OnHealthChange")*/)
	void BP_OnStrengthChange(float Strength, float MaxStrength);

	UFUNCTION(BlueprintImplementableEvent/*, meta = (DisplayName = "OnHealthChange")*/)
	void BP_Die();
};
