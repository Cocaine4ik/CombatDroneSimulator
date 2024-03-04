// Combat Drone Simulator. All Rights Reserved.


#include "Weapons/CDSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

// Sets default values
ACDSBaseWeapon::ACDSBaseWeapon()
{
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ACDSBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh)
    checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count coudn't be less or equal zero"))
    checkf(DefaultAmmo.Clips > 0, TEXT("Clips count coudn't be less or equal zero"))

    CurrentAmmo = DefaultAmmo;
}

void ACDSBaseWeapon::MakeShot()
{
}

bool ACDSBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    if (!Pawn)
    {
        return false;
    }

    if (Pawn->IsPlayerControlled())
    {
        const auto Controller = Pawn->GetController<APlayerController>();
        if (!Controller)
        {
            return false;
        }

        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    }
    else
    {
        ViewLocation = GetMuzzleWorldLocation();
        ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    }
    return true;
}

FVector ACDSBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ACDSBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
    {
        return false;
    }

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ACDSBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld())
    {
        return;
    }

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    CollisionParams.bReturnPhysicalMaterial = true;

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
}

void ACDSBaseWeapon::DecreaseAmmo()
{
    if (CurrentAmmo.Bullets == 0)
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("Clip is empty!"));
        return;
    }
    CurrentAmmo.Bullets--;
    UE_LOG(LogBaseWeapon, Warning, TEXT("Decrease Ammo %i"),CurrentAmmo.Bullets);

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("Reload"));
        StopFire();
        OnClipEmpty.Broadcast();
    }
}

bool ACDSBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

void ACDSBaseWeapon::StartFire()
{
    bFireInProgress = true;
    UE_LOG(LogBaseWeapon, Warning, TEXT("Fire!"));

}

void ACDSBaseWeapon::StopFire()
{
    bFireInProgress = false;
}

bool ACDSBaseWeapon::IsFiring() const
{
    return bFireInProgress;
}

void ACDSBaseWeapon::ChangeClip()
{
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;

    if (CurrentAmmo.Clips == 0)
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("No more clips!"));
        return;
    }
    CurrentAmmo.Clips--;
}

bool ACDSBaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool ACDSBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
    if (IsAmmoFull() || ClipsAmount <= 0)
    {
        return false;
    }

    if (IsAmmoEmpty())
    {
        UE_LOG(LogBaseWeapon, Display, TEXT("Ammo was empty"));

        // if clips num is one more + then default, we can add one - and after that make reload using OnClipEmpty event
        CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
        OnClipEmpty.Broadcast();
    }
    else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
    {
        const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
        if (DefaultAmmo.Clips - NextClipsAmount >= 0)
        {
            CurrentAmmo.Clips = NextClipsAmount;
            UE_LOG(LogBaseWeapon, Display, TEXT("Clips were added"));
        }
        // if difference between default clips and next clips < 0
        // so we take lot of clips =)
        else
        {
            // and we set all ammo to default value - restore is to full
            CurrentAmmo.Clips = DefaultAmmo.Clips;
            CurrentAmmo.Bullets = DefaultAmmo.Bullets;
            UE_LOG(LogBaseWeapon, Display, TEXT("Ammo is full now"));
        }
    }
    else
    {
        // if clips if full - restore bullets to default value
        CurrentAmmo.Bullets = DefaultAmmo.Bullets;
        UE_LOG(LogBaseWeapon, Display, TEXT("Ammo were added"));
    }
    return true;
}

bool ACDSBaseWeapon::IsAmmoEmpty() const
{
    return CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ACDSBaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;

}