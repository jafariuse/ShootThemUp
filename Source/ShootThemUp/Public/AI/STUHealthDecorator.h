// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUHealthDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUHealthDecorator : public UBTDecorator
{
  

    GENERATED_BODY()
public: 
    USTUHealthDecorator();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float HealthPercent = .6f;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
