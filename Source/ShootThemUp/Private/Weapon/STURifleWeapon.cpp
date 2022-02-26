// Shoot them up game


#include "Weapon/STURifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void ASTURifleWeapon::DrawImpact(FHitResult HitResult)
{

    WeaponFXComponent->PlayImpactFX(HitResult);
    MakeDamage(HitResult);
    
}

void ASTURifleWeapon::DrawShot(const FVector &TraceStart, const FVector &TraceEnd)
{
    SpawnTraceFX(TraceStart, TraceEnd);
}

void ASTURifleWeapon::SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd)
{
   const auto TraceComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),TraceFX,TraceStart);
    if (TraceComponent)
    {
        TraceComponent->SetNiagaraVariableVec3(TraceTargetName,TraceEnd);
        
    }
    
}

