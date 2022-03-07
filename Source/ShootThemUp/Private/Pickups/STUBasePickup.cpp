// Shoot them up game


#include "Pickups/STUBasePickup.h"

#include "Components/SphereComponent.h"

// Sets default values
ASTUBasePickup::ASTUBasePickup()
{
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent ->InitSphereRadius(CollisionRadius);
    SetRootComponent(CollisionComponent);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovementComponent");
    
	PrimaryActorTick.bCanEverTick = true;

}

bool ASTUBasePickup::CouldBeTaken() const
{
    return GetWorldTimerManager().IsTimerActive(RespawmTimerHandle);
}


void ASTUBasePickup::SetYaw()
{
    RotationYaw = FMath::RandRange(0.f,180.0f);
    const FRotator Rotator = FRotator{0,RotationYaw,0};
    RotatingMovementComponent->RotationRate = Rotator;
}

// Called when the game starts or when spawned
void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
    check(CollisionComponent);
	SetYaw();
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    const auto Pawn = Cast<APawn>(OtherActor);
    if (CanPickup(Pawn))
    {
        PickupTaken();
    };
        
}

// Called every frame
void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTUBasePickup::PickupTaken()
{
  
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    GetRootComponent()->SetVisibility(false,true);
    GetWorldTimerManager().SetTimer(RespawmTimerHandle,this,&ASTUBasePickup::Respawn,RespawnTime);
}

void ASTUBasePickup::Respawn()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    GetRootComponent()->SetVisibility(true,true);
    SetYaw();
}

