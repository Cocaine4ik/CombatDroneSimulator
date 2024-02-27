// Copyright Epic Games, Inc. All Rights Reserved.

#include "CombatDroneSimulatorGameMode.h"
#include "CombatDroneSimulatorCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACombatDroneSimulatorGameMode::ACombatDroneSimulatorGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
