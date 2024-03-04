// Combat Drone Simulator. All Rights Reserved.


#include "Pickups/CDSAmmoPickup.h"
#include "CDSHealthComponent.h"
#include "CDSWeaponComponent.h"

bool ACDSAmmoPickup::GivePickupTo(APawn* Pawn)
{
    if (!Pawn) return false;
    
    const auto HealthComponent = Pawn->GetComponentByClass<UCDSHealthComponent>();
    if(!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = Pawn->GetComponentByClass<UCDSWeaponComponent>();
    if(!WeaponComponent) return false;
    
    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}