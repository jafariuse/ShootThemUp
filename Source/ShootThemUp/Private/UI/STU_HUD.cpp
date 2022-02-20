// Shoot them up game


#include "UI/STU_HUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

void ASTU_HUD::DrawHUD()
{
    Super::DrawHUD();

   // DrawCrossHair();
}


void ASTU_HUD::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerHudWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHudVidgetClass);
    if(PlayerHudWidget)
    {
        PlayerHudWidget->AddToViewport(0);
    };
    
}

void ASTU_HUD::DrawCrossHair() 
{
    float CenterX = 0.0f;
    float CenterY = 0.0f;
    Canvas->GetCenter(CenterX, CenterY);
    constexpr float HalfLineSize = 10.0f;
    constexpr float lineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::White;

    DrawLine(CenterX - HalfLineSize, CenterY, CenterX + HalfLineSize, CenterY, LineColor, lineThickness);
    DrawLine(CenterX, CenterY - HalfLineSize, CenterX, CenterY + HalfLineSize, LineColor, lineThickness);


}
