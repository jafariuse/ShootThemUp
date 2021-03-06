// Shoot them up game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"


class USTUWeaponComponent;
class ASTUBaseWeapon;
class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;


UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUWeaponComponent *WeaponComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);
    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

  

	
	virtual void BeginPlay() override;
    virtual  void OnDeath();
    

public:	
	
	virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
	UFUNCTION(BlueprintCallable, Category = "Movement")
    bool isRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetDirection() const;

    


  private:
    bool RunPressed = false;
    
    void MoveForward(float Amount);
    void MoveRight(float Amount);

	void OnStartRunning();
    void OnStopRunning();

    
    void OnHealthChanged(float Health, float HealthDelta) const;

    UFUNCTION()
    void OnGroundLanded(const FHitResult &Hit);
    
};
