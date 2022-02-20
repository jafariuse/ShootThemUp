// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STU_Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
UCLASS()
class SHOOTTHEMUP_API ASTU_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTU_Projectile();

  

    void SetShotDirection(const FVector &Vector)
    {
        ShotDirection = Vector;
    }

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent *CollisionComponent;
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent *MovementComponent;


    UPROPERTY(EditAnywhere, Category = "Weapon")
    float CollisionRadius = 5.0f;
    UPROPERTY(EditAnywhere, Category = "Weapon")
    float Damage = 100.0f;
    UPROPERTY(EditAnywhere, Category = "Weapon")
    float DamageRadius = 100.0f;
   
    

    // Called when the game starts or when spawned
	virtual void BeginPlay() override;
   


	
private:
  FVector ShotDirection;

    AController * GetController() const;
    UFUNCTION()
    void OnProjetileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
};
