// Combat Drone Simulator. All Rights Reserved.


#include "Pickups/CDSBasePickup.h"
#include "Animation/AnimInstanceProxy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ACDSBasePickup::ACDSBasePickup()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACDSBasePickup::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent)

    GenerateRotationYaw();
}

void ACDSBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if(GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
    else if (Pawn)
    {
        OverlappingPawns.Add(Pawn);
    }
}

void ACDSBasePickup::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);
    
    const auto Pawn = Cast<APawn>(OtherActor);
    OverlappingPawns.Remove(Pawn);
}

bool ACDSBasePickup::CouldBeTaken() const
{
    return GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

bool ACDSBasePickup::GivePickupTo(APawn* Pawn)
{
    return false;
}

void ACDSBasePickup::PickupWasTaken()
{
    if(GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);    
    }
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());

    if (!bCanRespawn) return;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ACDSBasePickup::Respawn, RespawnTime);
}

void ACDSBasePickup::Respawn()
{
    GenerateRotationYaw();
    
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if(GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);    
    }
}

void ACDSBasePickup::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

// Called every frame
void ACDSBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));

    for(const auto OverlapPawn : OverlappingPawns)
    {
        if(GivePickupTo(OverlapPawn))
        {
            PickupWasTaken();
            break;
        }
    }
}