// Combat Drone Simulator. All Rights Reserved.


#include "Pickups/CDSHealthPickup.h"

#include "CDSHealthComponent.h"

bool ACDSHealthPickup::GivePickupTo(APawn* Pawn)
{
    if (!Pawn) return false;
    
    const auto HealthComponent = Pawn->GetComponentByClass<UCDSHealthComponent>();
    if(!HealthComponent || HealthComponent->IsDead()) return false;
    
    return HealthComponent->TryToAddHealth(HealthAmount);
}