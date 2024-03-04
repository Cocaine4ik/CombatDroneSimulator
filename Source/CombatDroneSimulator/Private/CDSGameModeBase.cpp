// Combat Drone Simulator. All Rights Reserved.


#include "CDSGameModeBase.h"
#include "Player/CDSPlayerPawn.h"
#include "Player/CDSPlayerController.h"
#include "UI/CDSGameHUD.h"

ACDSGameModeBase::ACDSGameModeBase()
{
    DefaultPawnClass = ACDSPlayerPawn::StaticClass();
    PlayerControllerClass = ACDSPlayerController::StaticClass();
    HUDClass = ACDSGameHUD::StaticClass();
}