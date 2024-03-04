// Combat Drone Simulator. All Rights Reserved.


#include "Weapons/CDSLauncherWeapon.h"
#include "Weapons/CDSProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LauncherWeapon, All, All)

ACDSLauncherWeapon::ACDSLauncherWeapon()
{
    DamageAmount = 40.0f;
}

void ACDSLauncherWeapon::MakeShot()
{
    if (!GetWorld()) return;

    if(IsAmmoEmpty())
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
        return;
    }
    
    FVector TraceStart, TraceEnd;
    if(!GetTraceData(TraceStart, TraceEnd)) return;
    
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FVector SpawnLocation = GetMuzzleWorldLocation() + ProjectileSpawnOffset;
    FTransform SpawnTransform(Direction.Rotation(), SpawnLocation);
    
    ACDSProjectile* Projectile = GetWorld()->SpawnActorDeferred<ACDSProjectile>(ProjectileClass, SpawnTransform);
    if(Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetDamageAmount(DamageAmount);
        Projectile->SetDamageRadius(DamageRadius);
        Projectile->SetDoFullDamage(bDoFullDamage);
        Projectile->SetOwner(GetOwner());
        
        // DrawDebugDirectionalArrow(GetWorld(), SpawnLocation, SpawnLocation + Projectile->GetActorForwardVector() * 100.0f, 20.0f, FColor::Red, false, 2.0f);
        
        Projectile->FinishSpawning(SpawnTransform);
        
    }
    DecreaseAmmo();
    
    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}

void ACDSLauncherWeapon::StartFire()
{
    Super::StartFire();
    MakeShot();
}