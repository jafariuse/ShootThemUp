// Shoot them up game



#include "AI/STUAICharacter.h"

#include "BrainComponent.h"
#include "AI/STUAIController.h"
#include "Components/STU_AI_WeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer &ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTU_AI_WeaponComponent>("WeaponComponent"))
{
    
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASTUAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if(GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f,200.0f,0.0f);
    }
}

void ASTUAICharacter::OnDeath()
{
    Super::OnDeath();
    const auto STUController = Cast<AAIController>(Controller);
    if(!STUController&&STUController->BrainComponent)
    {
        STUController->BrainComponent->Cleanup();
    }
}
