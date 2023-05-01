#include "CBoxUI.h"
#include "ChessBoardUI.h"

#include <Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h>

void UCBoxUI::Set(UChessBoardUI* _ChessBoardUI, int32 _X, int32 _Y, FLinearColor _Color, FLinearColor _OutlineColor)
{
	ChessBoardUI = _ChessBoardUI;
	Coord = { _X, _Y };
	DefaultColor = _Color;
	OutlineColor = _OutlineColor;

	SetColor(DefaultColor);
}
void UCBoxUI::UpdateSelection(bool bSelected)
{
	if (bSelected) SetColor(OutlineColor);
	else SetColor(DefaultColor);
}
void UCBoxUI::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::OnMouseEnter(InGeometry, InMouseEvent);

	ChessBoardUI->OnMouseEnter(Coord);
}

/*FReply UCBoxUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag: On Mouse Button Down"));

	FEventReply reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return reply.NativeReply;
}*/