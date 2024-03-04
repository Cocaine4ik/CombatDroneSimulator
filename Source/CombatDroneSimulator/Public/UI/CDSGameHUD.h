// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CDSGameHUD.generated.h"

class UUserWidget;

UCLASS()
class COMBATDRONESIMULATOR_API ACDSGameHUD : public AHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UUserWidget* PlayerHUDWidget;
};