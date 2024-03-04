// Combat Drone Simulator. All Rights Reserved.


#include "Player/CDSPlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CDSWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

ACDSPlayerPawn::ACDSPlayerPawn()
{
    // Rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = true;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = true;
    
    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(RootComponent);
    FirstPersonCamera->FieldOfView = 140.0f;

    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
    MovementComponent->SetUpdatedComponent(RootComponent);

    MovementComponent->MaxSpeed = 600.0f;
    MovementComponent->Acceleration = 300.0f;
    MovementComponent->Deceleration = 600.0f;

    BoxComponent->SetBoxExtent(FVector(110.0f, 120.0f, 20.0f));
}

void ACDSPlayerPawn::Move(const FInputActionValue& Value)
{
    FVector MovemementVector = Value.Get<FVector>();

    if (Controller != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Vector: %s"), *MovemementVector.ToString());
        
        AddMovementInput(GetActorForwardVector(), MovemementVector.Y);
        AddMovementInput(GetActorRightVector(), MovemementVector.X);
        AddMovementInput(GetActorUpVector(), MovemementVector.Z);
    }
}

void ACDSPlayerPawn::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void ACDSPlayerPawn::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void ACDSPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACDSPlayerPawn::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACDSPlayerPawn::Look);

        if (WeaponComponent)
        {
            EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, WeaponComponent, &UCDSWeaponComponent::StartFire);
        }
    }
}

void ACDSPlayerPawn::OnDeath()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}