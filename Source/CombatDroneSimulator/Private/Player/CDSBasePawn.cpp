// Combat Drone Simulator. All Rights Reserved.


#include "Player/CDSBasePawn.h"
#include "Components/CDSHealthComponent.h"
#include "Components/CDSWeaponComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ACDSBasePawn::ACDSBasePawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
    RootComponent = BoxComponent;

    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
    MeshComponent->SetupAttachment(RootComponent);
    
    HealthComponent = CreateDefaultSubobject<UCDSHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<UCDSWeaponComponent>("WeaponComponent");
}

void ACDSBasePawn::OnHealthChanged(float Health, float HealthDelta)
{
}

void ACDSBasePawn::OnDeath()
{
    Destroy();
}

// Called when the game starts or when spawned
void ACDSBasePawn::BeginPlay()
{
    Super::BeginPlay();

    check(MeshComponent)
    check(HealthComponent);

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ACDSBasePawn::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ACDSBasePawn::OnHealthChanged);
}

// Called every frame
void ACDSBasePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACDSBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

USkeletalMeshComponent* ACDSBasePawn::GetMesh() const
{
    return MeshComponent;
}