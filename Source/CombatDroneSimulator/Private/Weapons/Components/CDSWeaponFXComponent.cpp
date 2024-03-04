// Combat Drone Simulator. All Rights Reserved.

#include "Weapons/Components/CDSWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

UCDSWeaponFXComponent::UCDSWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UCDSWeaponFXComponent::PlayImpactEffects(const FHitResult& Hit)
{
    auto ImpactData = DefaultImpactData;

    if(Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if(ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }
    
    // spawn niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), //
        ImpactData.NiagaraEffect,                              //
        Hit.ImpactPoint,                                       //
        Hit.ImpactNormal.Rotation());

    // sound
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.Sound, Hit.ImpactPoint);
}

