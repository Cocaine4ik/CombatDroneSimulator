// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/CDSBasePawn.h"
#include "InputActionValue.h"
#include "CDSPlayerPawn.generated.h"

class UFloatingPawnMovement;
class UInputAction;
class UInputMappingContext;
class UBoxComponent;
class UCameraComponent;

UCLASS()
class COMBATDRONESIMULATOR_API ACDSPlayerPawn : public ACDSBasePawn
{
    GENERATED_BODY()

public:
    ACDSPlayerPawn();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UFloatingPawnMovement* MovementComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FirstPersonCamera;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Input")
    UInputMappingContext* DefaultMappingContext;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* FireAction;
    
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    
    virtual void BeginPlay() override;
    
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    virtual void OnDeath() override;
};