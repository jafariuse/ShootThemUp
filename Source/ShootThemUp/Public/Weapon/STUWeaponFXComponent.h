// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraSystem.h"
#include "STUCoreTypes.h"
#include "STUWeaponFXComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponFXComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FX")
    FImpactData DefaultImpactData;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FX")
    TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void PlayImpactFX(const FHitResult& HitResult);
		
};
