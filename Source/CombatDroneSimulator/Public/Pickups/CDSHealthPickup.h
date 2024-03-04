// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/CDSBasePickup.h"
#include "CDSHealthPickup.generated.h"

UCLASS()
class COMBATDRONESIMULATOR_API ACDSHealthPickup : public ACDSBasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "0", ClampMax = "1000"))
    float HealthAmount = 50.0f;

private:
    virtual bool GivePickupTo(APawn* Pawn) override;
};