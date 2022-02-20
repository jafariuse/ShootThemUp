// Shoot them up game


#include "Components/STUCharacterMovementController.h"
#include <Player/STUBaseCharacter.h>

float USTUCharacterMovementController::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASTUBaseCharacter *Player = Cast<ASTUBaseCharacter>(GetPawnOwner());

    return Player && Player->isRunning() ? RunModifier * MaxSpeed : MaxSpeed;
}