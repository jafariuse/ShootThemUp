// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"



class USkeletalMeshComponent;



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
    bool CanReload() const { return Ammo<WeaponConf.AmmoClip&&Clips >0;};
    
    FWeaponUIData GetWeaponUiData() const {return WeaponUiData;}
    FAmmoData GetAmmoData() const;

    UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Source Size", Keywords = "Source Texture Sprite"), Category = "UI") 
    static FVector2D GetSourceSize(UPaperSprite* Sprite);



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



    FTimerHandle TimerHandle_Fire;
    FTimerHandle TimerHandle_Recoil;

    FVector GetMuzzleLocation() const;

    void MakeHit(FHitResult& HitResult, FVector TraceStart, FVector TraceEnd) const;  
    bool GetPlayerController(APlayerController* &Controller) const;
    void Recoil() const;

    virtual void BeginPlay() override;
    virtual void MakeDamage(FHitResult HitResult);
    
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;
    
    virtual void DrawShot();

    bool IsClipEmpty() const
    {
        return Ammo <=MinAmmo;
    }

    bool IsAmmoEmpty() const
    {
        return IsClipEmpty()&& Clips <1;
    }
    virtual void MakeShot();
   
    virtual float TimeRemaining(FTimerHandle Timer) const;
 private:

    int32 MinAmmo = 0;
    int32 Ammo = 0;
    int32 Clips = 0;
    float FireRate = 0.f;

 
};
