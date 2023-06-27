// Copyright Neoxyne. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GCDemoTarget : TargetRules
{
	public GCDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("GCDemo");
	}
}
