// Shoot them up game


#include "AI/Services/STUFireService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUWeaponComponent.h"

USTUFireService::USTUFireService()
{
    NodeName = "Fire";
}

void USTUFireService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{

    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const bool HasAim = Blackboard&&Blackboard->GetValueAsObject((EnemyActorKey.SelectedKeyName));
    {
        if (Controller)
        {
            const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USTUWeaponComponent>();
            if(WeaponComponent)
            {
                HasAim? WeaponComponent->FireStart():WeaponComponent->FireStop();            
            }
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
