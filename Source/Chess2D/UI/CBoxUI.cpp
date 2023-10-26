#include "CBoxUI.h"
#include "Components/Image.h"
#include "../ChessComponent.h"

void UCBoxUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCBoxUI::Set(UChessComponent& _ChessComponent, FCCoord _CCoord, FLinearColor _Color, FLinearColor _SelectionColor)
{
	ChessComponent = &_ChessComponent;
	CCoord = _CCoord;
	DefaultColor = _Color;
	SelectionColor = _SelectionColor;
	BackgroundImage->Brush.TintColor = DefaultColor;

	UE_LOG(LogTemp, Warning, TEXT("[UCBoxUI] %s Created."), *CCoord.Name);
}

void UCBoxUI::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ChessComponent->SetCurrentCBoxUI(*this);
	BackgroundImage->Brush.TintColor = SelectionColor;
}

void UCBoxUI::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	ChessComponent->ClearCurrentCBoxUI();
	BackgroundImage->Brush.TintColor = DefaultColor;
}

void UCBoxUI::SetPieceTexture(UTexture2D* Image)
{
	if (Image)
	{
		PieceImage->SetBrushFromTexture(Image);
		PieceImage->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
	}
	else
	{
		PieceImage->SetBrushFromSoftTexture(nullptr);
		PieceImage->SetColorAndOpacity(FLinearColor(1, 1, 1, 0));
	}

}