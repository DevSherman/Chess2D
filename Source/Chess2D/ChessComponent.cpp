#include "ChessComponent.h"
#include "UI/ChessBoardUI.h"
#include "UI/CBoxUI.h"
#include "Utls.h"

UChessComponent::UChessComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UChessComponent::CreateBoard()
{
	Pieces_Textures = Utls::LoadTexturesFromPath("/Game/Textures/Pieces/");

	W_ChessBoardUI = Utls::LoadBlueprintFromPath<UChessBoardUI>("'/Game/Widgets/W_ChessBoardUI.W_ChessBoardUI'");
	ChessBoardUI = CreateWidget<UChessBoardUI>(GetWorld(), W_ChessBoardUI);
	if (!ChessBoardUI) { UE_LOG(LogTemp, Error, TEXT("[UChessComponent: %s] UI not initilizaed.")); return; }

	ChessBoardUI->AddToViewport();
	ChessBoardUI->Init(*this);

	UE_LOG(LogTemp, Warning, TEXT("[UChessComponent] Board Created."));

	SpawnPiece(EPieceType::WHITE_ROOK, EColor::WHITE, 0, 0);
	SpawnPiece(EPieceType::WHITE_KNIGHT, EColor::WHITE, 1, 0);
	SpawnPiece(EPieceType::WHITE_BISHOP, EColor::WHITE, 2, 0);
	SpawnPiece(EPieceType::WHITE_QUEEN, EColor::WHITE, 3, 0);
	SpawnPiece(EPieceType::WHITE_KING, EColor::WHITE, 4, 0);
	SpawnPiece(EPieceType::WHITE_BISHOP, EColor::WHITE, 5, 0);
	SpawnPiece(EPieceType::WHITE_KNIGHT, EColor::WHITE, 6, 0);
	SpawnPiece(EPieceType::WHITE_ROOK, EColor::WHITE, 7, 0);

	SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 0, 1);
	SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 1, 1);
	SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 2, 1);
	SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 3, 1);
	SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 4, 1);
	SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 5, 1);
	SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 6, 1);
	SpawnPiece(EPieceType::WHITE_PAWN, EColor::WHITE, 7, 1);

	SpawnPiece(EPieceType::BLACK_ROOK, EColor::BLACK, 0, 7);
	SpawnPiece(EPieceType::BLACK_KNIGHT, EColor::BLACK, 1, 7);
	SpawnPiece(EPieceType::BLACK_BISHOP, EColor::BLACK, 2, 7);
	SpawnPiece(EPieceType::BLACK_QUEEN, EColor::BLACK, 3, 7);
	SpawnPiece(EPieceType::BLACK_KING, EColor::BLACK, 4, 7);
	SpawnPiece(EPieceType::BLACK_BISHOP, EColor::BLACK, 5, 7);
	SpawnPiece(EPieceType::BLACK_KNIGHT, EColor::BLACK, 6, 7);
	SpawnPiece(EPieceType::BLACK_ROOK, EColor::BLACK, 7, 7);

	SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 0, 6);
	SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 1, 6);
	SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 2, 6);
	SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 3, 6);
	SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 4, 6);
	SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 5, 6);
	SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 6, 6);
	SpawnPiece(EPieceType::BLACK_PAWN, EColor::BLACK, 7, 6);

	UE_LOG(LogTemp, Warning, TEXT("[UChessComponent] Pieces placed."));


}

void UChessComponent::RegistryCBoxUI(UCBoxUI& CBoxUI)
{
	int X = CBoxUI.GetCoord().X;
	int Y = CBoxUI.GetCoord().Y;

	CBoxUIArray[X][Y] = &CBoxUI;
}

void UChessComponent::SetCurrentCBoxUI(UCBoxUI& CBoxUI)
{
	CurrentCBoxUI = &CBoxUI;
	
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("CurrentCBoxUI: [%s]"), *CurrentCBoxUI->GetCoord().Name));
}

void UChessComponent::UpdateCBoxData(EPieceType PieceType, EColor PieceColor, int X, int Y)
{
	CBData[X][Y] = new CBoxData(PieceType, PieceColor);
}

void UChessComponent::SpawnPiece(EPieceType PieceType, EColor PieceColor, int X, int Y)
{
	UpdateCBoxData(PieceType, PieceColor, X, Y);
	CBoxUIArray[X][Y]->SetPieceTexture(Pieces_Textures[PieceType]);
}
