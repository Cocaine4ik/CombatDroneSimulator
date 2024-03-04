// Combat Drone Simulator. All Rights Reserved.


#include "AI/CDSAIPawn.h"
#include "AI/CDSAIController.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CDSHealthComponent.h"
#include "Logging/LogMacros.h"
#include "Net/Core/Connection/NetResult.h"
#include "UI/CDSHealthBarWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUAICharacter, All, All)

ACDSAIPawn::ACDSAIPawn()
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ACDSAIController::StaticClass();

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidget");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

ACDSAIController* ACDSAIPawn::GetAIController() const
{
    return AIController;
}

void ACDSAIPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UpdateHealthWidgetVisibility();
}

void ACDSAIPawn::SetAIController()
{
    AIController = Cast<ACDSAIController>(GetController());
}

void ACDSAIPawn::BeginPlay()
{
    Super::BeginPlay();

    SetAIController();
    
    check(HealthWidgetComponent);
}

void ACDSAIPawn::OnDeath()
{
    Super::OnDeath();
    
    if (AIController && AIController->BrainComponent)
    {
        AIController->BrainComponent->Cleanup();
    }
}

void ACDSAIPawn::OnHealthChanged(float Health, float HealthDelta)
{
    Super::OnHealthChanged(Health, HealthDelta);

    const auto HealthBarWidget = Cast<UCDSHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!HealthBarWidget)
    {
        return;
    }
    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void ACDSAIPawn::UpdateHealthWidgetVisibility()
{
    if (!GetWorld() ||                             //
    !GetWorld()->GetFirstPlayerController() || //
    !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
        return;

    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
    HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}