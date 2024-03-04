// Combat Drone Simulator. All Rights Reserved.


#include "UI/CDSPlayerHUDWidget.h"
#include "CDSHealthComponent.h"
#include "CDSWeaponComponent.h"
#include "Components/ProgressBar.h"

float UCDSPlayerHUDWidget::GetHealthPercent() const
{
    if (!GetOwningPlayerPawn()) return 0.0f;
    
    const auto HealthComponent = GetOwningPlayerPawn()->GetComponentByClass<UCDSHealthComponent>();
    if (!HealthComponent)
    {
        return 0.0f;
    }

    return HealthComponent->GetHealthPercent();
}

bool UCDSPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    if (!GetOwningPlayerPawn()) return false;
    
    const auto WeaponComponent = GetOwningPlayerPawn()->GetComponentByClass<UCDSWeaponComponent>();
    if (!WeaponComponent)
    {
        return false;
    }

    return WeaponComponent->GetWeaponUIData(UIData);
}

FString UCDSPlayerHUDWidget::GetCurrentBulletsUIText() const
{
    FAmmoData CurrentAmmo;
    if (GetCurrentAmmoData(CurrentAmmo))
    {
        return FString::FromInt(CurrentAmmo.Bullets);
    }
    return FString(TEXT("Error"));
}

FString UCDSPlayerHUDWidget::GetCurrentClipsUIText() const
{
    FAmmoData CurrentAmmo;
    if (GetCurrentAmmoData(CurrentAmmo))
    {
        return FString::FromInt(CurrentAmmo.Clips);
    }
    return FString(TEXT("Error"));
}

void UCDSPlayerHUDWidget::NativeOnInitialized()
{
    if (!GetOwningPlayerPawn()) return;
    
    const auto HealthComponent = GetOwningPlayerPawn()->GetComponentByClass<UCDSHealthComponent>();
    if(HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &UCDSPlayerHUDWidget::OnHealthChanged);
    }
    UpdateHealthBar();
}

bool UCDSPlayerHUDWidget::GetCurrentAmmoData(FAmmoData& CurrentAmmo) const
{
    if (!GetOwningPlayerPawn()) return false;
    
    const auto WeaponComponent = GetOwningPlayerPawn()->GetComponentByClass<UCDSWeaponComponent>();
    if(!WeaponComponent) return false;
    return WeaponComponent->GetCurrentAmmoData(CurrentAmmo);
}

void UCDSPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if(HealthDelta < 0.0f)
    {
        OnTakeDamage();
    }
    UpdateHealthBar();
}

void UCDSPlayerHUDWidget::UpdateHealthBar()
{
    if(HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
    }
}