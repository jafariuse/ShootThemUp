// Shoot them up game


#include "Weapon/STULauncherWeapon.h"

#include "DrawDebugHelpers.h"
#include "Weapon/STU_Projectile.h"


void ASTULauncherWeapon::DrawShot(FHitResult HitResult)
{
   
   

    const FVector EndPoint =    HitResult.ImpactPoint;
    const FVector Direction = (EndPoint - GetMuzzleLocation()).GetSafeNormal();
    //DrawDebugLine(GetWorld(), GetMuzzleLocation(), EndPoint, FColor::Green, false, 3.0f, 0, 3.f);

   
    //const FTransform SpawnTransform(Direction.Rotation(), GetMuzzleLocation());
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleLocation());
    ASTU_Projectile* Projectile = GetWorld()->SpawnActorDeferred<ASTU_Projectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }

}
