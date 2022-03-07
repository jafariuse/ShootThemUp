// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_PickupCouldBeTaken : public UEnvQueryTest
{
    UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer);
    

    GENERATED_BODY()
protected:
    virtual void RunTest(FEnvQueryInstance &QueryInstance) const override;
};
