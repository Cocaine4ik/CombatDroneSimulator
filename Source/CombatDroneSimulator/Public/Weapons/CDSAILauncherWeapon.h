// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/CDSLauncherWeapon.h"
#include "CDSAILauncherWeapon.generated.h"

UCLASS()
class COMBATDRONESIMULATOR_API ACDSAILauncherWeapon : public ACDSLauncherWeapon
{
    GENERATED_BODY()

    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
};