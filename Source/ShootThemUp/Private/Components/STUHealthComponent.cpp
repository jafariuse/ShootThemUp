// Shoot them up game


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Player/STUPlayerController.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
    
	// ...
}


bool USTUHealthComponent::TryAddHealth(float HealSize)
{
    if (isDead()||HealthFull()) return false;
    SetHealth(Health + HealSize);
    return true;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    check(MaxHealth>0);
    check(CameraShake);

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
    PlayCameraShake();
	if (isDead())
        OnDeath.Broadcast();
    else if (AutoHeal && !FMath::IsNearlyEqual(Health,MaxHealth))
    {
        GetWorld()->GetTimerManager().SetTimer(TimerHandle_HealTimer, this, &USTUHealthComponent::DoHeal,
                                               HealUpdateTimer, true, HealDelay);
    }
}

void USTUHealthComponent::SetHealth(float newHealth)
{   float HealthDelta = Health;
    Health = FMath::Clamp(newHealth , 0.0f, MaxHealth);
    HealthDelta -= Health; 
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool USTUHealthComponent::HealthFull()
{
    return FMath::IsNearlyEqual(Health, MaxHealth) ;
}

void USTUHealthComponent::DoHeal()
{
    
    SetHealth(Health + HealModifier);

    if (HealthFull()&& GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HealTimer);
    }
}

void USTUHealthComponent::PlayCameraShake() const
{
    if(isDead())return;
    const auto Player = Cast<APawn>(GetOwner());
    if(!Player) return;
    const auto Controller  = Player->GetController<APlayerController>();
    if (!Controller||!Controller->PlayerCameraManager) return;
    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

