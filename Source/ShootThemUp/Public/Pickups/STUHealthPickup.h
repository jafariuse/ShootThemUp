// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
	GENERATED_BODY()
public:
    virtual bool CanPickup(APawn *PlayerPawn) const override;
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup",meta=(ClampMin="0.0",ClampMax="120.0"))
    float HealSize = 50.0f;
};
