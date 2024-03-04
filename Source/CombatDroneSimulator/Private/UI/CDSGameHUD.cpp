// Combat Drone Simulator. All Rights Reserved.

#include "UI/CDSGameHUD.h"
#include "Blueprint/UserWidget.h"

void ACDSGameHUD::BeginPlay()
{
    Super::BeginPlay();

    check(PlayerHUDWidgetClass)
    
    PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);

    PlayerHUDWidget->AddToViewport();
    PlayerHUDWidget->SetVisibility(ESlateVisibility::Visible);
}