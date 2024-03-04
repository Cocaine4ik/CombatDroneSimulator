// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDSStructs.h"
#include "Weapons/CDSBaseWeapon.h"
#include "CDSWeaponComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

class ACDSBaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COMBATDRONESIMULATOR_API UCDSWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCDSWeaponComponent();

    virtual void StartFire();
    void StopFire();
    void Reload();
    bool IsFiring() const;

    bool GetWeaponUIData(FWeaponUIData& UIData)const;
    bool GetCurrentAmmoData(FAmmoData& CurrentAmmo) const;

    bool TryToAddAmmo(TSubclassOf<ACDSBaseWeapon> WeaponType, int32 ClipsAmount);
    bool NeedAmmo(TSubclassOf<ACDSBaseWeapon> WeaponType);

    ACDSBaseWeapon* GetCurrentWeapon();
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ACDSBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponSocketName = "WeaponSocket";
    
    UPROPERTY(EditAnywhere, Category = "Weapon")
    float ReloadDuration = 1.0f;
    
    UPROPERTY()
    ACDSBaseWeapon* CurrentWeapon = nullptr;

    // Timer handle to manage the timer
    FTimerHandle ReloadTimerHandle;
    
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool bReloading = false;
    
private:
    void SpawnWeapon();
    void AttachWeaponToSocket(ACDSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    
    bool CanReload() const;

    UFUNCTION()
    void OnEmptyClip();
    
    void ChangeClip();
};