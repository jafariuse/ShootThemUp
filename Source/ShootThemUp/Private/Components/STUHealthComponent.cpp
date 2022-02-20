// Shoot them up game


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    check(MaxHealth>0);

	SetHealth(MaxHealth);
    

	AActor *ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }

	
}


// Called every frame
void USTUHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USTUHealthComponent::OnTakeAnyDamage(AActor *DamageActor, const float Damage, const class UDamageType *DamageType,
                     class AController *InstigateBy, AActor *DamageCauser)
{
    if (isDead()||!GetWorld()) return;
    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HealTimer);
    
	if (isDead())
        OnDeath.Broadcast();
    else if (AutoHeal && !FMath::IsNearlyEqual(Health,MaxHealth))
    {
        GetWorld()->GetTimerManager().SetTimer(TimerHandle_HealTimer, this, &USTUHealthComponent::DoHeal,
                                               HealUpdateTimer, true, HealDelay);
    }
}

void USTUHealthComponent::SetHealth(float newHealth)
{
    Health = FMath::Clamp(newHealth , 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}

void USTUHealthComponent::DoHeal()
{
    
    SetHealth(Health + HealModifier);

    if (FMath::IsNearlyEqual(Health,MaxHealth)&&GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HealTimer);
    }
}

