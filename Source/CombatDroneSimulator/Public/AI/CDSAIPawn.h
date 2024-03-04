// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/CDSBasePawn.h"
#include "CDSAIPawn.generated.h"

class UBehaviorTree;
class UWidgetComponent;
class ACDSAIController;

UCLASS()
class COMBATDRONESIMULATOR_API ACDSAIPawn : public ACDSBasePawn
{
    GENERATED_BODY()

public:
    ACDSAIPawn();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

    ACDSAIController* GetAIController() const;
    
    virtual void Tick(float DeltaSeconds) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float HealthVisibilityDistance = 1000.0f;

    UPROPERTY()
    ACDSAIController* AIController;
    
    void SetAIController();
    
    virtual void BeginPlay() override;
    
    virtual void OnDeath() override;
    virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
    void UpdateHealthWidgetVisibility();
};