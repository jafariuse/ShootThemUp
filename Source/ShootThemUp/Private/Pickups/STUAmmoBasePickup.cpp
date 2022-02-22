// Shoot them up game


#include "Pickups/STUAmmoBasePickup.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

bool ASTUAmmoBasePickup::CanPickup(APawn *PlayerPawn) const
{
    const auto HealthComponent = FStuUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    if(!HealthComponent||HealthComponent->isDead()) return false;
    const auto WeaponComponent = FStuUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
    if(!WeaponComponent) return false;
    return WeaponComponent->TryAddAmmo(WeaponType, AmmoAmount);
    
}
