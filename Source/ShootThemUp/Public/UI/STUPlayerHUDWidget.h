// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="UI")
    float GetHealthPercent() const;
    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetHealth() const;

    UFUNCTION(BlueprintImplementableEvent, Category="UI")
    void OnTakeDamage();
    
    UFUNCTION(BlueprintCallable, Category="UI")
    bool GetWeaponUIData(FWeaponUIData& WeaponUIData) const;
    UFUNCTION(BlueprintCallable, Category="UI")
    FString GetAmmoString() const;
    UFUNCTION(BlueprintCallable, Category="UI")
    bool IsPlayerAlive() const;
    UFUNCTION(BlueprintCallable, Category="UI")
    bool IsPlayerSpectating() const;
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UTexture2D* HitTexture;

    virtual bool Initialize() override;
    
private:
    void OnHealthChanged(float Health, float HealthDelta);
};
