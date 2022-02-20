// Shoot them up game


#include "Weapon/STURifleWeapon.h"

#include "DrawDebugHelpers.h"

/* void ASTURifleWeapon::FireStart()
{
    MakeShot();
    GetWorldTimerManager().SetTimer(TimerHandle_Fire, this, &ASTURifleWeapon::MakeShot,60 / WeaponConf.BMP,true);

}

void ASTURifleWeapon::FireStop()
{
    GetWorldTimerManager().ClearTimer(TimerHandle_Fire);
}

void ASTURifleWeapon::MakeShot()
{
    if (!GetWorld())
        return;
    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart,TraceEnd))return;
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);
    if (HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        DrawDebugLine(GetWorld(), GetMuzzleLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.f);
    }
}
*/