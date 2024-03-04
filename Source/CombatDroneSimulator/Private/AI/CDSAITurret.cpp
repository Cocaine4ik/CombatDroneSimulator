// Combat Drone Simulator. All Rights Reserved.


#include "AI/CDSAITurret.h"

#include "CDSWeaponComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI/CDSAIController.h"

DEFINE_LOG_CATEGORY_STATIC(AITurret, All, All)

ACDSAITurret::ACDSAITurret()
{
    StandMesh = CreateDefaultSubobject<UStaticMeshComponent>("StandMesh");
    StandMesh->SetupAttachment(RootComponent);
}

void ACDSAITurret::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    if (AIController && AIController->GetFocusActor())
    {
        RotateTowardsFocusActor(AIController->GetFocusActor());
    }
}

void ACDSAITurret::RotateTowardsFocusActor(const AActor* FocusActor)
{
    if (!FocusActor)
    {
        return;
    }

    const FVector DirectionToFocusActor = FocusActor->GetActorLocation() - GetActorLocation();
    const FRotator RotationToFocusActor = UKismetMathLibrary::MakeRotFromX(DirectionToFocusActor);
    
    FRotator ClampedRotation = FRotator(FMath::Clamp(RotationToFocusActor.Pitch, MinPitch, MaxPitch), RotationToFocusActor.Yaw,
        RotationToFocusActor.Roll);

    if (!WeaponComponent && !WeaponComponent->GetCurrentWeapon()) return;
    
    WeaponComponent->GetCurrentWeapon()->SetActorRotation(ClampedRotation);

    const FRotator LegRotationToFocusActor = FRotator(0.0f, ClampedRotation.Yaw, ClampedRotation.Roll);
    MeshComponent->SetWorldRotation(LegRotationToFocusActor);

}