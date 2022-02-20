// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponComponent();
    void FireStart();
    void FireStop();
    void Reload();
    void NextWeapon();

    bool GetWeaponUIData(FWeaponUIData& WeaponUIData) const;
    FString GetAmmoString() const;
 



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

public:	
	
private:
    UPROPERTY()
    ASTUBaseWeapon *CurrentWeapon = nullptr;
    UPROPERTY()
    TArray<ASTUBaseWeapon *> Weapons;
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage; 
  
    int32 CurrentWeaponIndex=0;
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(ASTUBaseWeapon *Weapon, const FName& SocketName) const;
    void EquipWeapon(int32 WeaponIndex);
    void PlayAnimMontage(UAnimMontage* AnimMontage) const;
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
    void OnEmptyClip();

    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;

    
};
