// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "STUWeaponFXComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"


UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
    ASTURifleWeapon();
    
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "FX")
    USTUWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
protected:
    virtual void DrawShot(FHitResult HitResult) override;
    
};
