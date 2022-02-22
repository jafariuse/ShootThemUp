// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

	UFUNCTION(BlueprintCallable, Category="Health")
    float GetHealth() const
    {
        return Health;
    }
    UFUNCTION(BlueprintCallable, Category="Health")
    float GetHealthPercent() const
	{
	    return Health/MaxHealth;
	}
    
    UFUNCTION(BlueprintCallable)
    bool isDead() const
    {
        return FMath::IsNearlyZero(Health);
    };
    UFUNCTION(BlueprintCallable)
  bool TryAddHealth(float HealSize);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClamMax = "10000.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal= true;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTimer = 0.3f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 1.0f;
    

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resistance", meta = (ClampMin = "-1.0", ClamMax = "1.0"))
    float FireResist = 0.5f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resistance", meta = (ClampMin = "-1.0", ClamMax = "1.0"))
    float IceResist = 0.5f;

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

private:
    float Health = 0.0f;
    FTimerHandle TimerHandle_HealTimer;
    

    UFUNCTION(BlueprintCallable)
    void OnTakeAnyDamage(AActor *DamageActor, const float Damage, const class UDamageType *DamageType,
                         class AController *InstigateBy, AActor *DamageCauser);
    void StartHeal();
    void SetHealth(float newHealth);
    bool HealthFull();
    void DoHeal();
};
