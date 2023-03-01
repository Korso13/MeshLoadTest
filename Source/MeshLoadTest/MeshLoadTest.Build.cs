// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MeshLoadTest : ModuleRules
{
	public MeshLoadTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
