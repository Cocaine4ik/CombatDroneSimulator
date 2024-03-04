// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AI/CDSAIPawn.h"
#include "CDSAITurret.generated.h"

UCLASS()
class COMBATDRONESIMULATOR_API ACDSAITurret : public ACDSAIPawn
{
    GENERATED_BODY()

public:
    ACDSAITurret();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USceneComponent* SceneComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* StandMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
    float MinPitch = -20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
    float MaxPitch = 20.0f;
    
    virtual void Tick(float DeltaSeconds) override;
private:
    void RotateTowardsFocusActor(const AActor* FocusActor);
};