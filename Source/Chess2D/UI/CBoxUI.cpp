#include "CBoxUI.h"
#include "Components/Image.h"
#include "../ChessComponent.h"

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

	UE_LOG(LogTemp, Warning, TEXT("[UCBoxUI] %s Created."), *Coord.GetName());
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
	PieceImage->SetBrushFromTexture(Image);
	PieceImage->SetOpacity(1);
}

void UCBoxUI::Clear()
{
	PieceImage->SetBrushFromSoftTexture(nullptr);
	PieceImage->SetOpacity(0);
}
