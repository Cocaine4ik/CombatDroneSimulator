// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDSProjectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UCDSWeaponFXComponent;

UCLASS()
class COMBATDRONESIMULATOR_API ACDSProjectile : public AActor
{
    GENERATED_BODY()
    
public:
    // Sets default values for this actor's properties
    ACDSProjectile();

    void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }
    void SetDamageAmount(const float Damage) { DamageAmount = Damage; }
    void SetDamageRadius(const float Radius) { DamageRadius = Radius; }
    void SetDoFullDamage(const bool DoFullDamage) { bDoFullDamage = DoFullDamage; }
    
protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UStaticMeshComponent* Mesh;
    
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UBoxComponent* BoxComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    float LifeTime = 5.0f;
    
    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UCDSWeaponFXComponent* WeaponFXComponent;
    
    virtual void BeginPlay() override;

private:
    FVector ShotDirection;
    float DamageAmount;
    float DamageRadius;
    bool bDoFullDamage;
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent*HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    AController* GetController() const;
};