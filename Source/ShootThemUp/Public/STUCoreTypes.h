#pragma once
#include "STUCoreTypes.generated.h"
class ASTUBaseWeapon;
DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);



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
    int32 Clips = 3;
    
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

