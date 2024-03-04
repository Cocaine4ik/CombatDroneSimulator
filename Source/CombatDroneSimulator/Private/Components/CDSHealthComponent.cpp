// Combat Drone Simulator. All Rights Reserved.


#include "Components/CDSHealthComponent.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
UCDSHealthComponent::UCDSHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UCDSHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0)
    
    SetHealth(MaxHealth);
    
    if (AActor* ComponentOwner = GetOwner())
    {
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &UCDSHealthComponent::OnTakeRadialDamage);
    }

}

bool UCDSHealthComponent::TryToAddHealth(float HealthAmount)
{
    if(IsHealthFull()) return false;
    
    SetHealth(Health + HealthAmount);
    UE_LOG(LogHealthComponent, Display, TEXT("Health points were restored"));
    return true;
}

bool UCDSHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UCDSHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, const FHitResult& HitInfo, class AController* InstigatedBy, AActor* DamageCauser)
{
    UE_LOG(LogHealthComponent, Display, TEXT("On radial damage: %f"), Damage);
    ApplyDamage(Damage, InstigatedBy);
}

void UCDSHealthComponent::SetHealth(const float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;
    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

void UCDSHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
    
    SetHealth(Health - Damage);
    
    if(IsDead())
    {
        OnDeath.Broadcast();
    }

    UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);
}
