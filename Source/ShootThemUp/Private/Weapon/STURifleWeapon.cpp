// Shoot them up game


#include "Weapon/STURifleWeapon.h"

#include "DrawDebugHelpers.h"


ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void ASTURifleWeapon::DrawShot(FHitResult HitResult)
{

    WeaponFXComponent->PlayImpactFX(HitResult);
    MakeDamage(HitResult);
    
}

