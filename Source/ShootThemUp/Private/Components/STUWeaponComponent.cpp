// Shoot them up game


#include "Components/STUWeaponComponent.h"

#include "Animations/AnimUtil.h"
#include "Animations/STUEquipFinishedAnimNotify.h"
#include "Animations/STUReloadingFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);
// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    SpawnWeapons();
    InitAnimations();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    
    CurrentWeapon = nullptr;
    for (auto Weapon :Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Super::EndPlay(EndPlayReason);
}


void USTUWeaponComponent::FireStart() 
{
    if (!CanFire()) return;
    CurrentWeapon->FireStart();
}
void USTUWeaponComponent::FireStop() 
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->FireStop();
}

void USTUWeaponComponent::Reload() 
{
    if (!CanReload()) return;
    FireStop();
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}

void USTUWeaponComponent::NextWeapon()
{
    if(!CanEquip()) return;
    FireStop();
    CurrentWeaponIndex =  (CurrentWeaponIndex +1) % Weapons.Num();
    
    EquipWeapon(CurrentWeaponIndex);
}




void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon *Weapon, const FName& SocketName) const
{
    const ACharacter *Character = Cast<ACharacter>(GetOwner());
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
if(WeaponIndex<0||WeaponIndex>=Weapons.Num()) return;
    if (CurrentWeapon)
    {
        AttachWeaponToSocket(CurrentWeapon, WeaponArmorySocketName);
    }
    CurrentWeapon = Weapons[WeaponIndex];
    const auto CurrentWeaponData = WeaponDatas.FindByPredicate([&](const FWeaponData& Data) //
        {return Data.WeaponClass == CurrentWeapon->GetClass();});                                     //
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
    
    AttachWeaponToSocket(CurrentWeapon, WeaponEquipPointName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage *AnimMontage) const
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character ||!GetWorld()) return;
    Character->PlayAnimMontage(AnimMontage);
}

void USTUWeaponComponent::InitAnimations()
{
    
    
    const auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        {EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);}
    }

    for (const FWeaponData WeaponData:WeaponDatas)
    {
        const auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTUReloadingFinishedAnimNotify>(WeaponData.ReloadAnimMontage);
        if (ReloadFinishedNotify)
        {
            {ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);}
        }
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character ||Character->GetMesh() != MeshComponent) return;
    EquipAnimInProgress = false;
 
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character ||Character->GetMesh() != MeshComponent) return;
    ReloadAnimInProgress = false;
    UE_LOG(LogTemp,Error, TEXT("OnReloadFinished"));
    CurrentWeapon->Reload();
 
}

void USTUWeaponComponent::OnEmptyClip()
{
    Reload();
}


bool USTUWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USTUWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress&& !ReloadAnimInProgress;
}

bool USTUWeaponComponent::CanReload() const
{
    return CurrentWeapon//  
    &&!ReloadAnimInProgress//   
    &&!EquipAnimInProgress//    
    &&CurrentWeapon->CanReload();   
}

void USTUWeaponComponent::SpawnWeapons()
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character ||!GetWorld()) return;

    for (auto WeaponData : WeaponDatas)
    {
        auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponData.WeaponClass);
        if(!Weapon) continue;
        Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);
        AttachWeaponToSocket(Weapon, WeaponArmorySocketName);
    }
}
