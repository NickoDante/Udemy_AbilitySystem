// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Udemy_AbilitySystem : ModuleRules
{
	public Udemy_AbilitySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayAbilities", "GameplayTags", "AIModule"});
	}
}
