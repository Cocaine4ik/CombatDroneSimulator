// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CDSAIController.generated.h"

class UCDSAIPerceptionComponent;

UCLASS()
class COMBATDRONESIMULATOR_API ACDSAIController : public AAIController
{
    GENERATED_BODY()

public:
    ACDSAIController();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    UCDSAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";
    
    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

private:
    AActor* GetFocusOnActor() const;
};