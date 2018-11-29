// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class OpenMOBAServerTarget : TargetRules
{
	public OpenMOBAServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;

		ExtraModuleNames.AddRange( new string[] { "OpenMOBA" } );
	}
}
