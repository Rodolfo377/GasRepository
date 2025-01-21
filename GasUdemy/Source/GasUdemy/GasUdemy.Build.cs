// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GasUdemy : ModuleRules
{
	public GasUdemy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "GameplayAbilities", "GameplayTags","InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks" });
	}
}
