// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUReloadService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUReloadService : public UBTService
{
	GENERATED_BODY()
public:
    USTUReloadService();
protected:
    

    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
    
	
};
