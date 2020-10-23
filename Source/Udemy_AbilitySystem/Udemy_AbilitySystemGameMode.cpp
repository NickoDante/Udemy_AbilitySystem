// Copyright Epic Games, Inc. All Rights Reserved.

#include "Udemy_AbilitySystemGameMode.h"
#include "Udemy_AbilitySystemHUD.h"
#include "Udemy_AbilitySystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUdemy_AbilitySystemGameMode::AUdemy_AbilitySystemGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUdemy_AbilitySystemHUD::StaticClass();
}
