// Shoot them up game


#include "AI/Services/STUReloadService.h"

#include "AIController.h"
#include "Components/STUWeaponComponent.h"

USTUReloadService::USTUReloadService()
{
 NodeName = "Reload";   
}

void USTUReloadService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{

    const auto Controller = OwnerComp.GetAIOwner();
    
        if (Controller)
        {
            const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USTUWeaponComponent>();
            if(WeaponComponent)
            {
                WeaponComponent->Reload();               
            }
        }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
