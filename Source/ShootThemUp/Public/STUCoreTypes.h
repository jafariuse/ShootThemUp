#pragma once

#include "PaperSprite.h"
#include "STUCoreTypes.generated.h"


class ASTUBaseWeapon;
class UNiagaraSystem;
DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_BODY()
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UPaperSprite* CrosshairIconSprite;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UPaperSprite* MainIconSprite;
        
    
};


USTRUCT(BlueprintType)
struct FWeaponConf
{
    GENERATED_USTRUCT_BODY()
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float WeaponPower = 15.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float BMP = 300.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float FireDelay = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    int32 AmmoClip = 30;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    int32 MaxAmmo = 150;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    bool Infinite = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float ReloadTime = 3.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 1.5f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    bool SingleAction = true;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    bool Projectile = false;
  
};

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    UAnimMontage* ReloadAnimMontage;
};
USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_BODY()
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    int32 Ammo = 0;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    int32 AmmoClip = 0;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    int32 Clips = 0;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    int32 MaxAmmo = 0;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    bool Infinite = false;
};

USTRUCT(BlueprintType)
struct FDecalData
{
    GENERATED_BODY()
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FX")
    UMaterialInterface* Material;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FX")
    FVector Size = FVector(10.0f);
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FX")
    float LifeTime = 5.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FX")
    float FadeOutTime = 5.0f;
};


USTRUCT(BlueprintType)
struct FImpactData
{
    GENERATED_BODY()
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FX")
    UNiagaraSystem* NiagaraEffect;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FX")
    FDecalData DecalData;
    

    
};
