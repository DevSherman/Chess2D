#include "CBoxUI.h"
#include "Components/Image.h"
#include "../ChessComponent.h"
#include "../Core/Utls.h"

void UCBoxUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCBoxUI::Set(UChessComponent& _ChessComponent, FCoord _Coord, FLinearColor _Color, FLinearColor _SelectionColor)
{
	ChessComponent = &_ChessComponent;
	Coord = _Coord;
	DefaultColor = _Color;
	SelectionColor = _SelectionColor;
	BackgroundImage->Brush.TintColor = DefaultColor;

	UE_LOG(LogTemp, Warning, TEXT("[UCBoxUI] %s Created."), *ChessUtls::GetCoordName(Coord));
}

void UCBoxUI::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ChessComponent->SetCurrentCBoxUI(*this);
	ShowSelection(true);
}

void UCBoxUI::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	ChessComponent->ClearCurrentCBoxUI();
	ShowSelection(false);
}

void UCBoxUI::ShowSelection(bool bValue)
{
	BackgroundImage->Brush.TintColor = bValue ? SelectionColor : DefaultColor;
}

void UCBoxUI::SetPieceTexture(UTexture2D* Texture)
{
	PieceImage->SetBrushFromTexture(Texture);
	PieceImage->SetOpacity(1);
}

void UCBoxUI::Clear()
{
	PieceImage->SetBrushFromSoftTexture(nullptr);
	PieceImage->SetOpacity(0);
}

