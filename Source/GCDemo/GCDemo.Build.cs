// Copyright Neoxyne. All Rights Reserved.

using UnrealBuildTool;

public class GCDemo : ModuleRules
{
	public GCDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "GameplayCurrency", "UMG" });
    }
}
