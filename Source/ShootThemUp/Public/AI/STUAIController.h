// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/STUAIPerceptionComponent.h"
#include "STUAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
	GENERATED_BODY()
    ASTUAIController();
    
protected:
    virtual void OnPossess(APawn *InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="Components")
    USTUAIPerceptionComponent * STUAIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="Components")
    FName FocusOnKeyName = "EnemyActor";

private:
    AActor* GetFocusOnActor() const;
    
};
