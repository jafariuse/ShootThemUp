// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "STUBasePickup.generated.h"

class USphereComponent;
UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASTUBasePickup();

    virtual bool CanPickup(APawn* PlayerPawn) const {return false;}


protected:
	UPROPERTY(VisibleAnywhere, Category="Pickup")
    USphereComponent* CollisionComponent;
    UPROPERTY(VisibleAnywhere, Category="Pickup")
    URotatingMovementComponent* RotatingMovementComponent;

    
    UPROPERTY(VisibleAnywhere, Category="Pickup")
    float CollisionRadius = 30.f;

    UPROPERTY(VisibleAnywhere, Category="Pickup")
    float RespawnTime = 10.f;

    void SetYaw();
    virtual void BeginPlay() override;

    virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
    float RotationYaw = 0.0f;
    void PickupTaken();
    void Respawn();

};
