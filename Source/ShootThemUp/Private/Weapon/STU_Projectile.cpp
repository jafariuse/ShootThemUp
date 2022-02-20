// Shoot them up game


#include "Weapon/STU_Projectile.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASTU_Projectile::ASTU_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(CollisionRadius);
    SetRootComponent(CollisionComponent);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
   
    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->ProjectileGravityScale = 0.0f;
   
}



// Called when the game starts or when spawned
void ASTU_Projectile::BeginPlay()
{
	Super::BeginPlay();
    
    check(MovementComponent);
    check(CollisionComponent);


    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASTU_Projectile::OnProjetileHit);

    SetLifeSpan(5.0f);
	
}

AController * ASTU_Projectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

void ASTU_Projectile::OnProjetileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                                     UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    if (!GetWorld()) return;
    MovementComponent->StopMovementImmediately();
    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red,false,5.0f);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), 
        {}, this,GetController(),false);

    Destroy();
}


