// Combat Drone Simulator. All Rights Reserved.


#include "Components/CDSAIPerceptionComponent.h"
#include "AIController.h"
#include "CDSPlayerPawn.h"
#include "Components/CDSHealthComponent.h"
#include "Perception/AISense_Sight.h"

DEFINE_LOG_CATEGORY_STATIC(AIPerceptionComponent, All, All)

AActor* UCDSAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PerceiveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
    if(PerceiveActors.Num() == 0) return nullptr;
    
    const auto Controller = Cast<AAIController>(GetOwner());
    if(!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if(!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;

    for(const auto PerceiveActor : PerceiveActors)
    {    
        const auto HealthComponent = PerceiveActor->GetComponentByClass<UCDSHealthComponent>();
        
        if(HealthComponent && !HealthComponent->IsDead() && CastChecked<ACDSPlayerPawn>(PerceiveActor))
        {
            const auto CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if(CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PerceiveActor;
            }
        } 
    }
    return BestPawn;
}