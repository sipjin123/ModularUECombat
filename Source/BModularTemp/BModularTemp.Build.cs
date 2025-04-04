// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BModularTemp : ModuleRules
{
	public BModularTemp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks" 
		});
	}
}
