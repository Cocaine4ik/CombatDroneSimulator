// Combat Drone Simulator. All Rights Reserved.


#include "AI/CDSAIController.h"
#include "Components/CDSAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/CDSAIPawn.h"

DEFINE_LOG_CATEGORY_STATIC(AIController, All, All)

ACDSAIController::ACDSAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UCDSAIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);
}

void ACDSAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AIPawn = Cast<ACDSAIPawn>(InPawn);
    if(AIPawn)
    {
        RunBehaviorTree(AIPawn->BehaviorTreeAsset);
    }
}

void ACDSAIController::Tick(float DeltaSeconds)
{
    const auto AimActor = AIPerceptionComponent->GetClosestEnemy();
    SetFocus(AimActor);
}

AActor* ACDSAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}