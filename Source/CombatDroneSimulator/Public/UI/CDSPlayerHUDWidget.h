// Combat Drone Simulator. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CDSStructs.h"
#include "CDSPlayerHUDWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class COMBATDRONESIMULATOR_API UCDSPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponUIData(FWeaponUIData& UIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetCurrentBulletsUIText() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetCurrentClipsUIText() const;
    
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold  = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor GoodColor  = FLinearColor::Green;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor BadColor  = FLinearColor::Red;

    virtual void NativeOnInitialized() override;
private:
    const int32 MaxLen = 2;
    const TCHAR PrefixSymbol = '0';
    
    bool GetCurrentAmmoData(FAmmoData& CurrentAmmo) const;

    void OnHealthChanged(float Health, float HealthDelta);

    void UpdateHealthBar();
};