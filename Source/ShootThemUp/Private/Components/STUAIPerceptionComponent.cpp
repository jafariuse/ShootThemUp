// Shoot them up game


#include "Components/STUAIPerceptionComponent.h"

#include "AIController.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"
AActor * USTUAIPerceptionComponent::GetClosesEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(),PercieveActors);
    if (PercieveActors.Num()==0) return nullptr;

    const auto Controller = Cast<AAIController>(GetOwner());
    if(!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if(!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;
    for (AActor* Actor:PercieveActors)
    {
        const auto HealthComponent = Actor->FindComponentByClass<USTUHealthComponent>();
        if(!HealthComponent||HealthComponent->isDead()) continue;
        const float Distance = Pawn->GetDistanceTo(Actor);
        if(Distance<BestDistance)
        {
            BestDistance = Distance;
            BestPawn = Actor;
        }
    }
    return BestPawn;
}
