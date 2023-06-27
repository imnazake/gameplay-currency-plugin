// Copyright Neoxyne. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GCDemoEditorTarget : TargetRules
{
	public GCDemoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("GCDemo");
	}
}
