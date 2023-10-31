#include "ChessBoardUI.h"

#include "../ChessComponent.h"
#include "Chess2D/Utls.h"
#include "CBoxUI.h"
#include "Components/WrapBox.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include <Blueprint/WidgetLayoutLibrary.h>

void UChessBoardUI::NativeConstruct()
{
	Super::NativeConstruct();
	CursorSlot = Cast<UCanvasPanelSlot>(CursorImage->Slot);
	CursorImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	ClearCursor();
}

FReply UChessBoardUI::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//UE_LOG(LogTemp, Warning, TEXT("[UChessBoardUI] NOnMouseMove"));
	CursorSlot->SetPosition(UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()));
	return FReply::Handled();
}

FReply UChessBoardUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ChessComponent->OnClickPressed();
	return FReply::Handled();
}

FReply UChessBoardUI::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ChessComponent->OnClickReleased();
	return FReply::Handled();
}

void UChessBoardUI::Init(UChessComponent& _ChessComponent)
{
	ChessComponent = &_ChessComponent;
	W_CBoxUI = Utls::LoadBlueprintFromPath<UCBoxUI>("/Game/Widgets/W_CBoxUI.W_CBoxUI");

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			int _y = 7 - y;

			UCBoxUI* CBoxUI = CreateWidget<UCBoxUI>(GetWorld(), W_CBoxUI);
			FCoord Coord{ x, _y};

			CBoxUI->Set
			(
				_ChessComponent,
				Coord,
				(x + _y) % 2 == 0 ? WHITE_COLOR : BLACK_COLOR,
				SELECTION_COLOR
			);
			ChessComponent->RegistryCBoxUI(*CBoxUI);
			ChessBoardBox->AddChild(CBoxUI);
		}
	}
}

void UChessBoardUI::SetCursorImage(UTexture2D* Texture)
{
	CursorImage->SetBrushFromTexture(Texture);
	CursorImage->SetOpacity(1);
}

UTexture2D* UChessBoardUI::GetImageFromCursor()
{
	return Cast<UTexture2D>(CursorImage->Brush.GetResourceObject());
}

void UChessBoardUI::ClearCursor()
{
	CursorImage->SetOpacity(0);
}
