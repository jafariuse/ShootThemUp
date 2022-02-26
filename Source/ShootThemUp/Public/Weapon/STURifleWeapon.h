// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "STUWeaponFXComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

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
    virtual void DrawImpact(FHitResult HitResult) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "FX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "FX")
    FString TraceTargetName = "TraceTarget";

    virtual void DrawShot(const FVector &TraceStart, const FVector &TraceEnd) override;
private:
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
};
