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
    
    
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    UE_LOG(LogTemp,Display,TEXT("Pwn"));
    Destroy();
    
}

// Called every frame
void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

