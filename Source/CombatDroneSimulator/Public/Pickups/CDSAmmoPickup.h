// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/CDSBasePickup.h"
#include "CDSAmmoPickup.generated.h"

class ACDSBaseWeapon;

UCLASS()
class COMBATDRONESIMULATOR_API ACDSAmmoPickup : public ACDSBasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = 10.0))
    int32 ClipsAmount = 10;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<ACDSBaseWeapon> WeaponType;
private:
    virtual bool GivePickupTo(APawn* Pawn) override;
};