// Shoot them up game


#include "AI/STUNextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "AI/STUAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUNextLocationTask::USTUNextLocationTask()
{
    NodeName = "Next Location";   
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if(!Controller || !Blackboard) return EBTNodeResult::Failed;

    const auto Pawn = Controller->GetPawn();
    if(!Pawn) return EBTNodeResult::Failed;

    const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
    if(!NavSys) return EBTNodeResult::Failed;
    FNavLocation NavLocation;

    FVector Location = Pawn->GetActorLocation();
    if (!SelfCenter)
    {
        const auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
        if(!CenterActor)
        {
            return EBTNodeResult::Failed;
        }
        Location = CenterActor->GetActorLocation();
    }    
    

    const bool IsFounded = NavSys->GetRandomReachablePointInRadius(Location,Radius,NavLocation);
    if(!IsFounded) return EBTNodeResult::Failed;

    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName,NavLocation);
    
    return EBTNodeResult::Succeeded;
}
