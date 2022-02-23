// Shoot them up game

#include "NiagaraFunctionLibrary.h"
#include "Weapon/STUWeaponFXComponent.h"

#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

#include <ratio>

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
    //UNiagaraSystem* Effect =DefaultImpactData.NiagaraEffect;
    FImpactData ImpactData = DefaultImpactData;
    if(HitResult.PhysMaterial.IsValid())
    {
        const auto PhysMat = HitResult.PhysMaterial.Get();
        if(ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap.FindRef(PhysMat);
        }
    }    
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),  //
        ImpactData.NiagaraEffect,                               //
        HitResult.ImpactPoint,                                  //
        HitResult.ImpactNormal.Rotation());
    const FDecalData DecalData = ImpactData.DecalData;
    const auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),          //
        DecalData.Material, //
        DecalData.Size, //   
        HitResult.ImpactPoint,  //
        HitResult.ImpactNormal.Rotation(),  //
        DecalData.LifeTime);
    if(Decal)
    {
        Decal->SetFadeOut(DecalData.LifeTime,DecalData.FadeOutTime);
    }
}

