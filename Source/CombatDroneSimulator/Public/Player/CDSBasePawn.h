// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CDSBasePawn.generated.h"

class UCDSHealthComponent;
class UCDSWeaponComponent;
class UBoxComponent;

UCLASS()
class COMBATDRONESIMULATOR_API ACDSBasePawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ACDSBasePawn();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* MeshComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UBoxComponent* BoxComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCDSHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCDSWeaponComponent* WeaponComponent;

    virtual void OnHealthChanged(float Health, float HealthDelta);
    virtual void OnDeath();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    USkeletalMeshComponent* GetMesh() const;
};