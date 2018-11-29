// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class OpenMOBAClientTarget : TargetRules
{
	public OpenMOBAClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;

		ExtraModuleNames.AddRange( new string[] { "OpenMOBA" } );
	}
}
