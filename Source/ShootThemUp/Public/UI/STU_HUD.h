// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STU_HUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTU_HUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> PlayerHudVidgetClass;

    virtual void BeginPlay() override;

private:
    void DrawCrossHair() ;
};
