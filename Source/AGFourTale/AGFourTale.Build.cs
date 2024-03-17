// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AGFourTale : ModuleRules
{
	public AGFourTale(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AnimGraphRuntime", "UMG", "DeveloperSettings" });
	}
}
