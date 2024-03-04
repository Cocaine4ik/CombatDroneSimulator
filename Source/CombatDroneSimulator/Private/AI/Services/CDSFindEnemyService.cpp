// Combat Drone Simulator. All Rights Reserved.


#include "AI/Services/CDSFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "CDSAIPerceptionComponent.h"

DEFINE_LOG_CATEGORY_STATIC(FindEnemyService, All, All)

UCDSFindEnemyService::UCDSFindEnemyService()
{
    NodeName = "Find Enemy";
}

void UCDSFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    if(BlackBoard)
    {    
        const auto Controller = OwnerComp.GetAIOwner();
        const auto AIPerceptionComponent = Controller->GetComponentByClass<UCDSAIPerceptionComponent>();
        if(AIPerceptionComponent)
        {
            BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName, AIPerceptionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}