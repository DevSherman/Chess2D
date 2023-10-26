#include "ChessBoardUI.h"

#include "../ChessComponent.h"
#include "Chess2D/Utls.h"
#include "CBoxUI.h"
#include "Components/WrapBox.h"

void UChessBoardUI::NativeConstruct()
{
	Super::NativeConstruct();
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
			FCCoord CCoord{ x, _y, Utls::GetCBoxName(x, _y) };

			CBoxUI->Set
			(
				_ChessComponent,
				CCoord,
				(x + _y) % 2 == 0 ? WHITE_COLOR : BLACK_COLOR,
				SELECTION_COLOR
			);
			ChessComponent->RegistryCBoxUI(*CBoxUI);
			ChessBoardBox->AddChild(CBoxUI);
		}
	}

	//X = COLUMN / Y = ROW
	ChessComponent->SpawnPiece(EPieceType::WHITE_ROOK, EColor::WHITE, 0, 0 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_KNIGHT, EColor::WHITE, 1, 0 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_BISHOP, EColor::WHITE, 2, 0 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_QUEEN, EColor::WHITE, 3, 0 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_KING, EColor::WHITE, 4, 0 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_BISHOP, EColor::WHITE, 5, 0 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_KNIGHT, EColor::WHITE, 6, 0 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_ROOK, EColor::WHITE, 7, 0 );
	
	ChessComponent->SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 0, 1 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 1, 1 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 2, 1 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 3, 1 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 4, 1 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 5, 1 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 6, 1 );
	ChessComponent->SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 7, 1 );
	
	ChessComponent->SpawnPiece(EPieceType::BLACK_ROOK, EColor::BLACK, 0, 7 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_KNIGHT, EColor::BLACK, 1, 7 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_BISHOP, EColor::BLACK, 2, 7 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_QUEEN, EColor::BLACK, 3, 7 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_KING, EColor::BLACK, 4, 7 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_BISHOP, EColor::BLACK, 5, 7 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_KNIGHT, EColor::BLACK, 6, 7 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_ROOK, EColor::BLACK, 7, 7 );
	
	ChessComponent->SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 0, 6 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 1, 6 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 2, 6 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 3, 6 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 4, 6 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 5, 6 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 6, 6 );
	ChessComponent->SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 7, 6 );
}
