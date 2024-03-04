// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDSBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class COMBATDRONESIMULATOR_API ACDSBasePickup : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACDSBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* Mesh;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* CollisionComponent; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    bool bCanRespawn = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundCue* PickupSound;
    
    UPROPERTY()
    TArray<APawn*> OverlappingPawns;
    
    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
    
public:
    virtual void Tick(float DeltaTime) override;
    bool CouldBeTaken() const;
    
private:
    float RotationYaw = 0.0f;
    FTimerHandle RespawnTimerHandle;
    
    virtual bool GivePickupTo(APawn* Pawn);
    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();

};