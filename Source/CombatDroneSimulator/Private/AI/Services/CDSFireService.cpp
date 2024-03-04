// Combat Drone Simulator. All Rights Reserved.


#include "AI/Services/CDSFireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CDSWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(FireService, All, All)

UCDSFireService::UCDSFireService()
{
    NodeName = "Fire";
}

void UCDSFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();

    const auto bHasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if(Controller)
    {
        const auto WeaponComponent = Controller->GetPawn()->GetComponentByClass<UCDSWeaponComponent>();
        if(WeaponComponent)
        {
            bHasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}