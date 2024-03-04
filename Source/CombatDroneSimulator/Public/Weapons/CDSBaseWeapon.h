// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDSStructs.h"
#include "CDSBaseWeapon.generated.h"

class USkeletalMeshComponent;
class USoundCue;

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

UCLASS()
class COMBATDRONESIMULATOR_API ACDSBaseWeapon : public AActor
{
    GENERATED_BODY()
public:
    // Sets default values for this actor's properties
    ACDSBaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

    virtual void StartFire();
    virtual void StopFire();
    bool IsFiring() const;

    void ChangeClip();
    bool CanReload() const;

    FWeaponUIData GetUIData() const { return UIData; }
    FAmmoData GetCurrentAmmoData() const {return CurrentAmmo; }

    bool TryToAddAmmo(int32 ClipsAmount);
    bool IsAmmoEmpty() const;
    bool IsAmmoFull() const;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    float DamageAmount = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{1, 3};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* FireSound;
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void MakeShot();
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

    void DecreaseAmmo();
    bool IsClipEmpty() const;
private:
    bool bFireInProgress = false;
    
    FAmmoData CurrentAmmo;
};