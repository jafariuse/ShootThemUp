// Shoot them up game


#include "AI/STUAmmoDecorator.h"

#include "AIController.h"
#include "Components/STUWeaponComponent.h"
#include "Components/STU_AI_WeaponComponent.h"

bool USTUAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USTU_AI_WeaponComponent>();
    if (!WeaponComponent) return false;
    return WeaponComponent->AmmoPercent(WeaponClass)<MinAmmo;
}
