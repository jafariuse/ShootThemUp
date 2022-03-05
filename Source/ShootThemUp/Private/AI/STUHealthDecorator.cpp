// Shoot them up game


#include "AI/STUHealthDecorator.h"

#include "AIController.h"
#include "Components/STUHealthComponent.h"

USTUHealthDecorator::USTUHealthDecorator()
{
    NodeName = "Health Percent";
}

bool USTUHealthDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto HealthComponent = Controller->GetPawn()->FindComponentByClass<USTUHealthComponent>();
    if (!HealthComponent|| HealthComponent->isDead()) return false;
    return  HealthComponent->GetHealthPercent()<=HealthPercent;
    
    
    return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
}
