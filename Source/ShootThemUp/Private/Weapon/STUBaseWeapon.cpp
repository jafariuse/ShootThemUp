// Shoot them up game


#include "Weapon/STUBaseWeapon.h"

#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
//#include "PaperSprite.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/STUWEaponFXComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);
// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh= CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshComponent");
    SetRootComponent(WeaponMesh);
    
    

}

void ASTUBaseWeapon::FireStart()
{
    if (!GetWorld()) return;
 
    
    MakeShot();
    
    if (!WeaponConf.SingleAction)
    {
        GetWorld()->GetTimerManager().SetTimer(TimerHandle_Fire, this, &ASTUBaseWeapon::MakeShot, FireRate, true);
    }
    
}

void ASTUBaseWeapon::FireStop()
{
    if (!GetWorld())
        return;
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Fire);
    if (MuzzleFxComponent)
    {
        SetMuzzleFXVisibility(false);
    }
}



bool ASTUBaseWeapon::ReadyToFire() const
{
    
    if (TimeRemaining(TimerHandle_Recoil)>0)
    {
//            UE_LOG(LogBaseWeapon, Display, TEXT("Recoil"));
            return false;
    }
    if (Ammo <= MinAmmo)
    {
//        UE_LOG(LogBaseWeapon, Display, TEXT("No Ammo"));
        return false;
    };
    return true;
}

FAmmoData ASTUBaseWeapon::GetAmmoData() const
{
   return FAmmoData{Ammo, WeaponConf.AmmoClip, Clips(), AllAmmo, WeaponConf.Infinite};
}

bool ASTUBaseWeapon::TryAddClips(const int32 AmmoAmount)
{
    if (WeaponConf.Infinite||AllAmmo==WeaponConf.MaxAmmo) return false;
    const int32 Delta = FMath::Min(WeaponConf.AmmoClip-Ammo,AllAmmo);
    Ammo += Delta;
    AllAmmo = FMath::Clamp(AllAmmo+AmmoAmount-Delta, AllAmmo, WeaponConf.MaxAmmo); 
    return true;
}
/*
FVector2D ASTUBaseWeapon::GetSourceSize(UPaperSprite *Sprite)
{
    return Sprite->GetSourceSize();
}
*/


// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
    FireRate = WeaponConf.BMP == 0 ? 0 : 60 / WeaponConf.BMP;
    check(WeaponMesh);
    AllAmmo = WeaponConf.MaxAmmo;
    Ammo = WeaponConf.AmmoClip;
    
	
}
float ASTUBaseWeapon::TimeRemaining(const FTimerHandle Timer) const
{
    float Remain = 0.0f;
    if (GetWorld())
    {
        if (!Timer.IsValid())
        {

            Remain = GetWorld()->GetTimerManager().GetTimerRemaining(Timer);
            if (FMath::IsNearlyZero(Remain)) Remain = 0.f;
                
        }
    }
    return FMath::Max(Remain, 0.f);
}

int32 ASTUBaseWeapon::Clips() const
{
    return AllAmmo/WeaponConf.AmmoClip;
}

void ASTUBaseWeapon::SetMuzzleFXVisibility(bool bCond)
{
    if(!MuzzleFxComponent)
    {
        MuzzleFxComponent = SpawnMuzzleFX();
    };
    MuzzleFxComponent->SetPaused(!bCond);
    MuzzleFxComponent->SetVisibility(bCond);
}

bool ASTUBaseWeapon::GetPlayerController(APlayerController*  &Controller) const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return true;

    Controller = Player->GetController<APlayerController>();
    if (!Controller) return true;
    return false;
}

void ASTUBaseWeapon::Reload()
{
    const int32 Delta = FMath::Min(WeaponConf.AmmoClip-Ammo,AllAmmo);
    Ammo += Delta;
    if(!WeaponConf.Infinite)
    {
        AllAmmo -= Delta;
    }     
    
}

void ASTUBaseWeapon::Recoil() const
{
//    UE_LOG(LogBaseWeapon, Display, TEXT("ding"));
}

UNiagaraComponent * ASTUBaseWeapon::SpawnMuzzleFX()

{
    
    
        return  UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFx,//
            WeaponMesh,//
            MuzzleSocketName,//
            FVector::ZeroVector,//
            FRotator::ZeroRotator,//
            EAttachLocation::SnapToTarget,//
            true);
    
    
    
}

bool ASTUBaseWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
    const auto STUCharacter = Cast<ACharacter>(GetOwner());
    if (!STUCharacter) return false;
    FVector ViewLocation;
    FRotator ViewRotation;
    
    if (STUCharacter->IsPlayerControlled())
    {
        APlayerController* Controller;
        if (GetPlayerController(Controller)) return false;

   
        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
 
    }
    else
    {
        ViewLocation = GetMuzzleLocation();
        ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    }

    
 
    
    
    const auto HalfRad  = FMath::DegreesToRadians(WeaponConf.BulletSpread);
    const FVector ShotDirection = FMath::VRandCone(ViewRotation.Vector(),HalfRad);

    //TraceStart = ViewLocation;
    TraceStart = GetMuzzleLocation();
    TraceEnd = ViewLocation + ShotDirection * TraceMaxDistance;
    return true;
}



void ASTUBaseWeapon::MakeDamage(FHitResult HitResult)
{
    auto const Victim = HitResult.GetActor();
    if (!Victim) return;
    ///////////
    float Crit = 1.f;
    if (HitResult.BoneName.ToString()=="b_Head") Crit = 100.f;
    /////
    Victim->TakeDamage(WeaponConf.WeaponPower*Crit, FDamageEvent{}, nullptr, this);
  //  UE_LOG(LogBaseWeapon, Display, TEXT("Bone:%s"), *HitResult.BoneName.ToString());
   
    
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, FVector TraceStart, FVector TraceEnd) const
{
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    CollisionQueryParams.bReturnPhysicalMaterial = true;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
                                         CollisionQueryParams);
}

FVector ASTUBaseWeapon::GetMuzzleLocation()const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

void ASTUBaseWeapon::DrawImpact(FHitResult HitResult)
{
    
    MakeDamage(HitResult);
}

void ASTUBaseWeapon::DrawShot(const FVector &TraceStart, const FVector &TraceEnd)
{
    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 3.0f, 0, 3.f);
}

void ASTUBaseWeapon::MakeShot()
{
    if (!ReadyToFire())
    {
       FireStop();
       return;
    }
    Ammo --;
    if (WeaponConf.SingleAction)
    {
        SpawnMuzzleFX();
    }
    else
    {
        SetMuzzleFXVisibility(true);
    };
    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        OnClipEmpty.Broadcast();
    };

   
    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;


    MakeHit(HitResult, TraceStart, TraceEnd);
    
    DrawShot(TraceStart,HitResult.bBlockingHit?HitResult.ImpactPoint:TraceEnd);
    if (HitResult.bBlockingHit)
    {
        DrawImpact(HitResult);
        
    }
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_Recoil, this, &ASTUBaseWeapon::Recoil, FireRate);
}



