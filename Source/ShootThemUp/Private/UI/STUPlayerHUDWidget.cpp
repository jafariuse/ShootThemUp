// Shoot them up game




#include "UI/STUPlayerHUDWidget.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

class USTUHealthComponent;

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const USTUHealthComponent* HealthComponent = FStuUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if(!HealthComponent) return 0.0f;
    return HealthComponent->GetHealthPercent();
}

int32 USTUPlayerHUDWidget::GetHealth() const
{
    const USTUHealthComponent* HealthComponent = FStuUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if(!HealthComponent) return 0;
    return FMath::RoundToFloat(HealthComponent->GetHealth());
}


bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData &WeaponUIData) const
{
    const USTUWeaponComponent* WeaponComponent = FStuUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
       
    if(!WeaponComponent) return false;
    return WeaponComponent->GetWeaponUIData(WeaponUIData);
}

FString USTUPlayerHUDWidget::GetAmmoString() const
{
    const USTUWeaponComponent* WeaponComponent = FStuUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComponent) return "";
    return WeaponComponent->GetAmmoString();
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    const USTUHealthComponent* HealthComponent = FStuUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    
    return  HealthComponent && !HealthComponent->isDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && (Controller->GetStateName()==NAME_Spectating);
}

bool USTUPlayerHUDWidget::Initialize()
{
    const auto HealthComponent = FStuUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if (HealthComponent)
    {
       HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
    }
    
    return Super::Initialize();
}

void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta) 
{
if (HealthDelta>0.0f)
{
    OnTakeDamage();
}
}
