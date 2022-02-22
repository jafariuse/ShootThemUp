// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"


class USTUWeaponFXComponent;
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
    ASTURifleWeapon();
public:
    /* virtual void FireStart() override;
	virtual void FireStop() override;
protected:
    virtual void MakeShot() override;
    FTimerHandle TimerHandle_Fire;*/
    
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="FX")
    USTUWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
  virtual void DrawShot() override;
};
