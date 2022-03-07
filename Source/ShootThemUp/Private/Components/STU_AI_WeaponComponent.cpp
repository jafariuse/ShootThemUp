// Shoot them up game


#include "Components/STU_AI_WeaponComponent.h"

void USTU_AI_WeaponComponent::FireStart()
{
    if (!CanFire()) return;
    if(CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->FireStart();
    }
    
}

void USTU_AI_WeaponComponent::NextWeapon()
{
    if(!CanEquip()) return;
    FireStop();
    int32 NextIndex = (CurrentWeaponIndex+1)%Weapons.Num();
    while (NextIndex !=CurrentWeaponIndex)
    {
        if(!Weapons[NextIndex]->IsAmmoEmpty()) break;
        NextIndex = (NextIndex+1) % Weapons.Num();
    }
    if (CurrentWeaponIndex != NextIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }   
    
}
