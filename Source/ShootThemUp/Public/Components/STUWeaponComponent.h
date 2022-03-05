// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Pickups/STUAmmoBasePickup.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponComponent();
    virtual void FireStart();
    void FireStop();
    void Reload();
    virtual void NextWeapon();

    bool GetWeaponUIData(FWeaponUIData& WeaponUIData) const;
    FString GetAmmoString() const;
    bool TryAddAmmo(const TSubclassOf<ASTUBaseWeapon> & Class, int32 AmmoClips);
    float AmmoPercent(const TSubclassOf<ASTUBaseWeapon> &Class) const;


protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponDatas;
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipPointName = "WeaponSocket";
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";
    UPROPERTY(EditDefaultsOnly, Category="Animation")
    UAnimMontage* EquipAnimMontage;
    


    // Called when the game starts
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    UPROPERTY()
    ASTUBaseWeapon *CurrentWeapon = nullptr;
    UPROPERTY()
    TArray<ASTUBaseWeapon *> Weapons;
    bool CanFire() const;
    bool CanEquip() const;
    void EquipWeapon(int32 WeaponIndex);
    int32 CurrentWeaponIndex=0;
    
private:
    
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage; 
  
    
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(ASTUBaseWeapon *Weapon, const FName& SocketName) const;
    void PlayAnimMontage(UAnimMontage* AnimMontage) const;
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
    void OnEmptyClip();
    bool CanReload() const;

    
};
