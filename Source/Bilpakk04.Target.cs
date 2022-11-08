// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Bilpakk04Target : TargetRules
{
	public Bilpakk04Target( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "Bilpakk04" } );
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		if (bBuildEditor)
		{
			ExtraModuleNames.AddRange(new string[] { "Bilpakk04Editor" });
		}
	}
}
