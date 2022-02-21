// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;
UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASTUBasePickup();

protected:
	UPROPERTY(VisibleAnywhere, Category="Pickup")
    USphereComponent* CollisionComponent;

    
    UPROPERTY(VisibleAnywhere, Category="Pickup")
    float CollisionRadius = 30.f;

    virtual void BeginPlay() override;

    virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
