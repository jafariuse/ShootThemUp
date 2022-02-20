// Shoot them up game


#include "Weapon/STUBaseWeapon.h"

#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);
// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh= CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshComponent");
    SetRootComponent(WeaponMesh);
    Clips = WeaponConf.Clips;

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
    
}



bool ASTUBaseWeapon::ReadyToFire() const
{
    
    if (TimeRemaining(TimerHandle_Recoil)>0)
    {
            UE_LOG(LogBaseWeapon, Display, TEXT("Recoil"));
            return false;
    }
    if (Ammo <= MinAmmo)
    {
        UE_LOG(LogBaseWeapon, Display, TEXT("No Ammo"));
        return false;
    };
    return true;
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
    FireRate = WeaponConf.BMP == 0 ? 0 : 60 / WeaponConf.BMP;
    check(WeaponMesh);
    
	
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
    Ammo = WeaponConf.AmmoClip;
    UE_LOG(LogBaseWeapon, Display, TEXT("Ready"));
    Clips --;
    
}

void ASTUBaseWeapon::Recoil() const
{
    UE_LOG(LogBaseWeapon, Display, TEXT("ding"));
}

bool ASTUBaseWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
    APlayerController* Controller;
    if (GetPlayerController(Controller)) return false;

    FVector ViewLocation;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

    
    
    const auto HalfRad  = FMath::DegreesToRadians(WeaponConf.BulletSpread);
    const FVector ShotDirection = FMath::VRandCone(ViewRotation.Vector(),HalfRad);

    TraceStart = ViewLocation;
    TraceEnd = TraceStart + ShotDirection * TraceMaxDistance;
    return true;
}



void ASTUBaseWeapon::MakeDamage(FHitResult HitResult)
{
    auto const Victim = HitResult.GetActor();
    if (!Victim) return;
    Victim->TakeDamage(WeaponConf.WeaponPower, FDamageEvent{}, nullptr, this);
    UE_LOG(LogBaseWeapon, Display, TEXT("Bone:%s"), *HitResult.BoneName.ToString());
   
    
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, FVector TraceStart, FVector TraceEnd) const
{
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
                                         CollisionQueryParams);
}

FVector ASTUBaseWeapon::GetMuzzleLocation()const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

void ASTUBaseWeapon::DrawShot()
{
    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;


    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), GetMuzzleLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.f);
        MakeDamage(HitResult);
       
    }
    
}

void ASTUBaseWeapon::MakeShot()
{
    if (!ReadyToFire())
    {
       FireStop();
       return;
    }
    Ammo --;
    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        OnClipEmpty.Broadcast();
    };

    DrawShot();
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_Recoil, this, &ASTUBaseWeapon::Recoil, FireRate);
}



