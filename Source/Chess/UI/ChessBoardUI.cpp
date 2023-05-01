#include "ChessBoardUI.h"

#include "Chess/Chess.h"
#include "Chess/Utls.h"
#include "CBoxUI.h"
#include "../Core/CBox.h"
#include "../MainController.h"

void UChessBoardUI::NativeConstruct()
{
	Super::NativeConstruct();

	Pieces_Textures = Utls::LoadTexturesFromPath("/Game/Pieces/");
	BP_CBoxUI = Utls::LoadBlueprintFromPath<UCBoxUI>("WidgetBlueprint'/Game/UI/W_CBoxUI.W_CBoxUI'");

	for (size_t y = 0; y < 8; y++)
	{
		for (size_t x = 0; x < 8; x++)
		{
			int32 _y = 7 - y;

			UCBoxUI* CBoxUI = CreateWidget<UCBoxUI>(GetWorld(), BP_CBoxUI);
			CBoxUI->Set
			(
				this,
				x, _y,
				(x + _y) % 2 == 0 ? WHITE_COLOR : BLACK_COLOR,
				SELECTION_COLOR
			);
			AddToGrid(CBoxUI);
			CBoxUIArray[x][_y] = CBoxUI;
		}
	}

	//X = COLUMN / Y = ROW
	UpdateCBoxUI(EPieceType::WHITE_ROOK, { 0, 0 }, true);
	UpdateCBoxUI(EPieceType::WHITE_KNIGHT, { 1, 0 }, true);
	UpdateCBoxUI(EPieceType::WHITE_BISHOP, { 2, 0 }, true);
	UpdateCBoxUI(EPieceType::WHITE_QUEEN, { 3, 0 }, true);
	UpdateCBoxUI(EPieceType::WHITE_KING, { 4, 0 }, true);
	UpdateCBoxUI(EPieceType::WHITE_BISHOP, { 5, 0 }, true);
	UpdateCBoxUI(EPieceType::WHITE_KNIGHT, { 6, 0 }, true);
	UpdateCBoxUI(EPieceType::WHITE_ROOK, { 7, 0 }), true;

	UpdateCBoxUI(EPieceType::WHITE_PAWN, { 0, 1 }, true);
	UpdateCBoxUI(EPieceType::WHITE_PAWN, { 1, 1 }, true);
	UpdateCBoxUI(EPieceType::WHITE_PAWN, { 2, 1 }, true);
	UpdateCBoxUI(EPieceType::WHITE_PAWN, { 3, 1 }, true);
	UpdateCBoxUI(EPieceType::WHITE_PAWN, { 4, 1 }, true);
	UpdateCBoxUI(EPieceType::WHITE_PAWN, { 5, 1 }, true);
	UpdateCBoxUI(EPieceType::WHITE_PAWN, { 6, 1 }, true);
	UpdateCBoxUI(EPieceType::WHITE_PAWN, { 7, 1 }, true);

	UpdateCBoxUI(EPieceType::BLACK_ROOK, { 0, 7 }, true);
	UpdateCBoxUI(EPieceType::BLACK_KNIGHT, { 1, 7 }, true);
	UpdateCBoxUI(EPieceType::BLACK_BISHOP, { 2, 7 }, true);
	UpdateCBoxUI(EPieceType::BLACK_QUEEN, { 3, 7 }, true);
	UpdateCBoxUI(EPieceType::BLACK_KING, { 4, 7 }, true);
	UpdateCBoxUI(EPieceType::BLACK_BISHOP, { 5, 7 }, true);
	UpdateCBoxUI(EPieceType::BLACK_KNIGHT, { 6, 7 }, true);
	UpdateCBoxUI(EPieceType::BLACK_ROOK, { 7, 7 }, true);

	UpdateCBoxUI(EPieceType::BLACK_PAWN, { 0, 6 }, true);
	UpdateCBoxUI(EPieceType::BLACK_PAWN, { 1, 6 }, true);
	UpdateCBoxUI(EPieceType::BLACK_PAWN, { 2, 6 }, true);
	UpdateCBoxUI(EPieceType::BLACK_PAWN, { 3, 6 }, true);
	UpdateCBoxUI(EPieceType::BLACK_PAWN, { 4, 6 }, true);
	UpdateCBoxUI(EPieceType::BLACK_PAWN, { 5, 6 }, true);
	UpdateCBoxUI(EPieceType::BLACK_PAWN, { 6, 6 }, true);
	UpdateCBoxUI(EPieceType::BLACK_PAWN, { 7, 6 }, true);
}

void UChessBoardUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateCursorPosition(Controller->GetMousePosition());
}

void UChessBoardUI::OnMouseEnter(FIntPoint _Coord)
{
	SetCurrentCBoxUI(_Coord);
}

void UChessBoardUI::SetCurrentCBoxUI(FIntPoint _Coord)
{
	UCBoxUI* CBoxFocus = GetCBoxUI(_Coord);

	if (CurrentCBoxUI != nullptr) CurrentCBoxUI->UpdateSelection(false);

	CurrentCBoxUI = CBoxFocus;
	CurrentCBoxUI->UpdateSelection(true);

	Controller->SetCurrentCBox(_Coord);
}

void UChessBoardUI::UpdateCBoxUI(EPieceType _Type, FIntPoint _Coord, bool bSpawn)
{
	GetCBoxUI(_Coord)->SetSprite(Pieces_Textures[_Type]);
	if (bSpawn) Controller->UpdateCBox(_Coord, new CBox(_Type));
}

void UChessBoardUI::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bMouseIn = true;
}
void UChessBoardUI::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	bMouseIn = false;
	CurrentCBoxUI->UpdateSelection(false);
}

