// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/CDSBaseWeapon.h"
#include "CDSLauncherWeapon.generated.h"

class ACDSProjectile;
class USoundCue;

UCLASS()
class COMBATDRONESIMULATOR_API ACDSLauncherWeapon : public ACDSBaseWeapon
{
    GENERATED_BODY()

public:
    ACDSLauncherWeapon();
    
    virtual void StartFire() override;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ACDSProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FVector ProjectileSpawnOffset {0.0f, 0.0f, 0.0f };
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    float DamageRadius = 200.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    bool bDoFullDamage = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* NoAmmoSound = nullptr;
    
    virtual void MakeShot() override;
    
};