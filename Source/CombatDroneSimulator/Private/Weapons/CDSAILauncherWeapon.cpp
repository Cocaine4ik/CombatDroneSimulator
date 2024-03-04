// Combat Drone Simulator. All Rights Reserved.


#include "Weapons/CDSAILauncherWeapon.h"
#include "CDSAIPawn.h"
#include "AI/CDSAIController.h"
#include "DrawDebugHelpers.h"

bool ACDSAILauncherWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    if (const auto AIPawn = Cast<ACDSAIPawn>(GetOwner()))
    {
        if(const auto AIController = AIPawn->GetAIController())
        {
            TraceStart = GetMuzzleWorldLocation();
            if (AIController->GetFocusActor())
            {
                const FVector ShootDirection = AIController->GetFocusActor()->GetActorLocation();
                TraceEnd = ShootDirection;

                // DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 2.0f, 0, 1.0f);
                return true;   
            }
        }
    }
    return false;
}