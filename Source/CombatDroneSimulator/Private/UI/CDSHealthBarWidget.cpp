// Combat Drone Simulator. All Rights Reserved.


#include "UI/CDSHealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Logging/LogMacros.h"

void UCDSHealthBarWidget::SetHealthPercent(float Percent)
{
    if(!HealthProgressBar) return;
    
    const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent)) //
                                         ? ESlateVisibility::Hidden
                                         : ESlateVisibility::Visible;
    HealthProgressBar->SetVisibility(HealthBarVisibility);

    const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
}