// Shoot them up game


#include "Weapon/STURifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "Weapon/STUWeaponFXComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void ASTURifleWeapon::DrawShot()
{
    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;


    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)
    {
        WeaponFXComponent->PlayImpactFX(HitResult);
        MakeDamage(HitResult);
       
    }
    
}
