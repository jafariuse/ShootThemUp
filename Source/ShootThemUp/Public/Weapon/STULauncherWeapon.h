// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTU_Projectile;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

protected:
	virtual void DrawShot(FHitResult HitResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTU_Projectile> ProjectileClass;
};
