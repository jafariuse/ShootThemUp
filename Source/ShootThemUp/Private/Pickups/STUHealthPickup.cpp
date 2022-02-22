// Shoot them up game


#include "Pickups/STUHealthPickup.h"

#include "STUUtils.h"
#include "Components/STUHealthComponent.h"

bool ASTUHealthPickup::CanPickup(APawn *PlayerPawn) const
{
    const auto HealthComponent = FStuUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    if(!HealthComponent||HealthComponent->isDead()) return false;
    return HealthComponent->TryAddHealth(HealSize);
}
