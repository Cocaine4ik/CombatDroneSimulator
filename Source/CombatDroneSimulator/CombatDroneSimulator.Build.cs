// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CombatDroneSimulator : ModuleRules
{
	public CombatDroneSimulator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"EnhancedInput",
			"Niagara",
			"GameplayTasks",
			"NavigationSystem",
			"PhysicsCore"
		});
		PublicIncludePaths.AddRange(new[]
		{
			"CombatDroneSimulator/Public/Player",
			"CombatDroneSimulator/Public/Components",
			"CombatDroneSimulator/Public/Pickups",
			"CombatDroneSimulator/Public/AI",
			"CombatDroneSimulator/Public/AI/Services",
			"CombatDroneSimulator/Public/UI",
			"CombatDroneSimulator/Public/Weapons",
			"CombatDroneSimulator/Public/Weapons/Components"
		});
	}
}
