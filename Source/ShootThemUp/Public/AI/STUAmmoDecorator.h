// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUAmmoDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUAmmoDecorator : public UBTDecorator
{
    USTUAmmoDecorator()
    {
        NodeName = "Ammo Percent";
    }

    GENERATED_BODY()
protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float MinAmmo = 0.6f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;
    
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
