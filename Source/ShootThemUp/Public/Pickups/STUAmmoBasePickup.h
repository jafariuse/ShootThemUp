// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUAmmoBasePickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAmmoBasePickup : public ASTUBasePickup
{
	GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup",meta=(ClampMin="1.0",ClampMax="1000.0"))
    int32 AmmoAmount = 5.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
    TSubclassOf<ASTUBaseWeapon> WeaponType;
    
public:
    virtual bool CanPickup(APawn *PlayerPawn) const override;
    
};
