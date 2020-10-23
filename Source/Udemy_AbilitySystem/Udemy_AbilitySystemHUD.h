// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Udemy_AbilitySystemHUD.generated.h"

UCLASS()
class AUdemy_AbilitySystemHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUdemy_AbilitySystemHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

