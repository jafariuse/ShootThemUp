// Shoot them up game


#include "Weapon/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USTUWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USTUWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult &HitResult)
{
   UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Effect,HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation()); 
}

