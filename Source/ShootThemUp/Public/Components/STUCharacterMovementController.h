// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUCharacterMovementController : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public: 
	virtual float GetMaxSpeed() const override;
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement",  meta =( ClampMin =1.0, ClampMax = 16.0))
	float RunModifier = 2.0f;
};
