// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "STUWEaponFXComponent.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"



class USkeletalMeshComponent;
class UNiagaraComponent;
class UPaperSprite;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    ASTUBaseWeapon();
    virtual void FireStart();
    virtual void FireStop();
    virtual void Reload();
    
    bool ReadyToFire() const;
    bool CanReload() const { return Ammo<WeaponConf.AmmoClip&&AllAmmo>0;};
    
    FWeaponUIData GetWeaponUiData() const {return WeaponUiData;}
    FAmmoData GetAmmoData() const;
    bool TryAddClips(const int32 AmmoAmount);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Source Size", Keywords = "Source Texture Sprite"), Category = "UI") 
     FVector2D GetSourceSize(UPaperSprite* Sprite);



    FOnClipEmptySignature OnClipEmpty;
  

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent *WeaponMesh;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleFlashSocket";
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FWeaponConf WeaponConf;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FWeaponUIData WeaponUiData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UNiagaraSystem* MuzzleFx;

    


    FTimerHandle TimerHandle_Fire;
    FTimerHandle TimerHandle_Recoil;

    FVector GetMuzzleLocation() const;

    void MakeHit(FHitResult& HitResult, FVector TraceStart, FVector TraceEnd) const;  
    bool GetPlayerController(APlayerController* &Controller) const;
    void Recoil() const;

    UNiagaraComponent * SpawnMuzzleFX();
    
    virtual void BeginPlay() override;
    virtual void MakeDamage(FHitResult HitResult);
    
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;
    
    virtual void DrawImpact(FHitResult HitResult);

    bool IsClipEmpty() const
    {
        return Ammo <=MinAmmo;
    }

    bool IsAmmoEmpty() const
    {
        return IsClipEmpty()&& Clips() <1;
    }

    virtual void DrawShot(const FVector & TraceStart, const FVector& TraceEnd);
    virtual void MakeShot();
   
    virtual float TimeRemaining(FTimerHandle Timer) const;
 private:
    int32 Clips() const;
    
    int32 MinAmmo = 0;
    int32 Ammo = 0;
    int32 AllAmmo = 0;
    float FireRate = 0.f;
    UPROPERTY()
    UNiagaraComponent * MuzzleFxComponent;
    void SetMuzzleFXVisibility(bool bCond);
 
};
