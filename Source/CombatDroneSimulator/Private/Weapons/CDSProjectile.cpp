// Combat Drone Simulator. All Rights Reserved.


#include "Weapons/CDSProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Components/CDSWeaponFXComponent.h"

// Sets default values
ACDSProjectile:: ACDSProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>("SphereComponent");
    BoxComponent->SetBoxExtent(FVector(35.0f, 6.0f, 6.0f));
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    BoxComponent->bReturnMaterialOnMove = true;
    SetRootComponent(BoxComponent);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    Mesh->SetupAttachment(RootComponent);
    
    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;
    
    WeaponFXComponent = CreateDefaultSubobject<UCDSWeaponFXComponent>("WeaponFXComponent");
}

// Called when the game starts or when spawned
void ACDSProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(BoxComponent)
    check(MovementComponent);
    check(MovementComponent->InitialSpeed != 0)
    check(MovementComponent->ProjectileGravityScale == 0.0f)
    
    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    BoxComponent->OnComponentHit.AddDynamic(this, &ACDSProjectile::OnHit);
    BoxComponent->IgnoreActorWhenMoving(GetOwner(), true);
    SetLifeSpan(LifeTime);

}

void ACDSProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
    const FHitResult& Hit)
{
    if(!GetWorld()) return;
    
    MovementComponent->StopMovementImmediately();

    // make damage
    UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius,
        UDamageType::StaticClass(), {},this, GetController(), bDoFullDamage);

    // DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);
    WeaponFXComponent->PlayImpactEffects(Hit);
    Destroy();
}

AController* ACDSProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
