// Shoot them up game


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/STUBaseWeapon.h"

#include <Components/InputComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/STUCharacterMovementController.h>
#include <Components/STUHealthComponent.h>
#include <Components/TextRenderComponent.h>
#include <GameFramework/Controller.h>

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer &ObjInit) 
    : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementController>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
   
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());

    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
    
    


}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent);

    OnHealthChanged(HealthComponent->GetHealth(),0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
    
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
   
} 

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ASTUBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::FireStart);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::FireStop);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);



}

bool ASTUBaseCharacter::isRunning() const
{
    
    
    return RunPressed && !GetVelocity().IsNearlyZero();
}

float ASTUBaseCharacter::GetDirection() const
{
    const FVector VelocityNormal = GetVelocity().GetSafeNormal();
    const FVector ActorForwardVector = GetActorForwardVector();
    const float AngleBetween = FMath::Acos(FVector::DotProduct(VelocityNormal, ActorForwardVector)); 
    const float CrossProduct = FVector::CrossProduct(VelocityNormal, ActorForwardVector).Z;
    return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct);

}

void ASTUBaseCharacter::MoveForward(float Amount)
{
    
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::OnStartRunning()
{
    RunPressed = true;
    

    
}
void ASTUBaseCharacter::OnStopRunning()
{
    RunPressed = false;
    
}

void ASTUBaseCharacter::OnDeath()
{
    //PlayAnimMontage(DeathAnimMontage);
    
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult &Hit)
{
    
    const auto FallVelocityZ = - GetCharacterMovement()->Velocity.Z;
   
    if (FallVelocityZ<LandedDamageVelocity.X) return;
    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}



void ASTUBaseCharacter::OnHealthChanged(const float Health, const float HealthDelta) const
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%0.f"), Health)));
}
