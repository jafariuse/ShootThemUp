// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "Components/STUWeaponComponent.h"
#include "STU_AI_WeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTU_AI_WeaponComponent : public USTUWeaponComponent
{
	GENERATED_BODY()
public:
    virtual void FireStart() override;
    virtual void NextWeapon() override;
};
