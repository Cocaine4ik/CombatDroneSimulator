// Combat Drone Simulator. All Rights Reserved.


#include "Components/CDSWeaponComponent.h"
#include "CDSBasePawn.h"
#include "Weapons/CDSBaseWeapon.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

UCDSWeaponComponent::UCDSWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UCDSWeaponComponent::StartFire()
{
    if (bReloading)
    {
        return;
    }
    CurrentWeapon->StartFire();
}

void UCDSWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
    {
        return;
    }
    CurrentWeapon->StopFire();
}

void UCDSWeaponComponent::Reload()
{
    ChangeClip();
}

bool UCDSWeaponComponent::IsFiring() const
{
    return CurrentWeapon && CurrentWeapon->IsFiring();
}

bool UCDSWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
    if (CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}

bool UCDSWeaponComponent::GetCurrentAmmoData(FAmmoData& CurrentAmmo) const
{
    if (CurrentWeapon)
    {
        CurrentAmmo = CurrentWeapon->GetCurrentAmmoData();
        return true;
    }
    return false;
}

bool UCDSWeaponComponent::TryToAddAmmo(TSubclassOf<ACDSBaseWeapon> WeaponType, int32 ClipsAmount)
{
    if (CurrentWeapon)
    {
        return CurrentWeapon->TryToAddAmmo(ClipsAmount);
    }
    return false;
}

bool UCDSWeaponComponent::NeedAmmo(TSubclassOf<ACDSBaseWeapon> WeaponType)
{
    if (CurrentWeapon)
    {
        return !CurrentWeapon->IsAmmoFull();
    }
    return false;
}

ACDSBaseWeapon* UCDSWeaponComponent::GetCurrentWeapon()
{
    return CurrentWeapon;
}

void UCDSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (CurrentWeapon)
    {
        CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        CurrentWeapon->Destroy(); 
    }
    Super::EndPlay(EndPlayReason);
}

void UCDSWeaponComponent::SpawnWeapon()
{
    auto Pawn = Cast<ACDSBasePawn>(GetOwner());
    if (!Pawn || !GetWorld())
    {
        return;
    }

    auto Weapon = GetWorld()->SpawnActor<ACDSBaseWeapon>(WeaponClass);
    if(!Weapon) return;
    
    Weapon->OnClipEmpty.AddUObject(this, &UCDSWeaponComponent::OnEmptyClip);
    Weapon->SetOwner(Pawn);
    CurrentWeapon = Weapon;
    AttachWeaponToSocket(Weapon, Pawn->GetMesh(), WeaponSocketName);
}


void UCDSWeaponComponent::AttachWeaponToSocket(ACDSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent) return;

    const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
    
    Weapon->AttachToComponent(SceneComponent, AttachmentTransformRules, SocketName);
}

bool UCDSWeaponComponent::CanReload() const
{
    return !bReloading && CurrentWeapon->CanReload();
}

void UCDSWeaponComponent::OnEmptyClip()
{
    // UE_LOG(LogWeaponComponent, Warning, TEXT("OnEmptyClip"));
    
    if(CurrentWeapon)
    {    
        bReloading = true;
        GetOwner()->GetWorldTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateLambda([this]()
        {
            this->bReloading = false;
            ChangeClip();
        }), ReloadDuration, false);
    }
}

void UCDSWeaponComponent::ChangeClip()
{
    if(!CanReload()) return;
    
    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();
}

// Called when the game starts
void UCDSWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    
    SpawnWeapon();
}