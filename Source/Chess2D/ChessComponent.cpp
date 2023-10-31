#include "ChessComponent.h"
#include "Core/ChessEngine.h"
#include "UI/ChessBoardUI.h"
#include "UI/CBoxUI.h"
#include "Core/ChessTypes.h"
#include "Utls.h"

UChessComponent::UChessComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Engine = NewObject<UChessEngine>();
}

void UChessComponent::CreateBoard()
{
	TexturesPieces = Utls::LoadTexturesFromPath("/Game/Textures/Pieces/");

	W_ChessBoardUI = Utls::LoadBlueprintFromPath<UChessBoardUI>("'/Game/Widgets/W_ChessBoardUI.W_ChessBoardUI'");
	UI = CreateWidget<UChessBoardUI>(GetWorld(), W_ChessBoardUI);
	if (!UI) { UE_LOG(LogTemp, Error, TEXT("[UChessComponent: %s] UI not initilizaed.")); return; }

	UI->AddToViewport();
	UI->Init(*this);

	UE_LOG(LogTemp, Warning, TEXT("[UChessComponent] Board Created."));

	SpawnPiece(EPieceType::ROOK, EPieceColor::WHITE, 0, 0);
	SpawnPiece(EPieceType::KNIGHT, EPieceColor::WHITE, 1, 0);
	SpawnPiece(EPieceType::BISHOP, EPieceColor::WHITE, 2, 0);
	SpawnPiece(EPieceType::QUEEN, EPieceColor::WHITE, 3, 0);
	SpawnPiece(EPieceType::KING, EPieceColor::WHITE, 4, 0);
	SpawnPiece(EPieceType::BISHOP, EPieceColor::WHITE, 5, 0);
	SpawnPiece(EPieceType::KNIGHT, EPieceColor::WHITE, 6, 0);
	SpawnPiece(EPieceType::ROOK, EPieceColor::WHITE, 7, 0);

	SpawnPiece(EPieceType::PAWN, EPieceColor::WHITE, 0, 1);
	SpawnPiece(EPieceType::PAWN, EPieceColor::WHITE, 1, 1);
	SpawnPiece(EPieceType::PAWN, EPieceColor::WHITE, 2, 1);
	SpawnPiece(EPieceType::PAWN, EPieceColor::WHITE, 3, 1);
	SpawnPiece(EPieceType::PAWN, EPieceColor::WHITE, 4, 1);
	SpawnPiece(EPieceType::PAWN, EPieceColor::WHITE, 5, 1);
	SpawnPiece(EPieceType::PAWN, EPieceColor::WHITE, 6, 1);
	SpawnPiece(EPieceType::PAWN, EPieceColor::WHITE, 7, 1);

	SpawnPiece(EPieceType::ROOK, EPieceColor::BLACK, 0, 7);
	SpawnPiece(EPieceType::KNIGHT, EPieceColor::BLACK, 1, 7);
	SpawnPiece(EPieceType::BISHOP, EPieceColor::BLACK, 2, 7);
	SpawnPiece(EPieceType::QUEEN, EPieceColor::BLACK, 3, 7);
	SpawnPiece(EPieceType::KING, EPieceColor::BLACK, 4, 7);
	SpawnPiece(EPieceType::BISHOP, EPieceColor::BLACK, 5, 7);
	SpawnPiece(EPieceType::KNIGHT, EPieceColor::BLACK, 6, 7);
	SpawnPiece(EPieceType::ROOK, EPieceColor::BLACK, 7, 7);

	SpawnPiece(EPieceType::PAWN, EPieceColor::BLACK, 0, 6);
	SpawnPiece(EPieceType::PAWN, EPieceColor::BLACK, 1, 6);
	SpawnPiece(EPieceType::PAWN, EPieceColor::BLACK, 2, 6);
	SpawnPiece(EPieceType::PAWN, EPieceColor::BLACK, 3, 6);
	SpawnPiece(EPieceType::PAWN, EPieceColor::BLACK, 4, 6);
	SpawnPiece(EPieceType::PAWN, EPieceColor::BLACK, 5, 6);
	SpawnPiece(EPieceType::PAWN, EPieceColor::BLACK, 6, 6);
	SpawnPiece(EPieceType::PAWN, EPieceColor::BLACK, 7, 6);

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
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("CurrentCBoxUI: [%s]"), *CurrentCBoxUI->GetCoord().GetName()));
}

void UChessComponent::UpdateBoard(ChessBoxData* Data)
{
	Engine->UpdateBoard(Data);
}

void UChessComponent::OnClickPressed()
{
	if (!CurrentCBoxUI) return;

	MoveToCursor();


}

void UChessComponent::OnClickReleased()
{
	if (CurrentData) //mouse slot data
	{
		if (CurrentCBoxUI) //move
		{
			CurrentCBoxUI->SetPieceTexture(UI->GetImageFromCursor());
			CurrentData->Coord = CurrentCBoxUI->GetCoord();
			Engine->UpdateBoard(CurrentData);
		}
	}

	UI->ClearCursor();
	CurrentData = nullptr;
}

void UChessComponent::MoveToCursor()
{
	CurrentData = &Engine->GetData(CurrentCBoxUI->GetCoord());
	UI->SetCursorImage(GetPieceTexture(CurrentData->PieceType, CurrentData->PieceColor));

	CurrentCBoxUI->Clear();

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("CurrentData: [%s]"), *CurrentData->Coord.GetName()));
}

void UChessComponent::SpawnPiece(EPieceType PieceType, EPieceColor PieceColor, int X, int Y)
{
	Engine->UpdateBoard(new ChessBoxData(PieceType, PieceColor, X, Y));
	CBoxUIArray[X][Y]->SetPieceTexture(GetPieceTexture(PieceType, PieceColor));
}

UTexture2D* UChessComponent::GetPieceTexture(EPieceType PieceType, EPieceColor PieceColor)
{
	if (PieceType == EPieceType::EMPTY || PieceColor == EPieceColor::NONE)
	{
		UE_LOG(LogTemp, Error, TEXT("[UChessComponent::GetPieceTexture] Invalid Data."));
		return nullptr;
	}

	int Index = PieceType;
	if (PieceColor == EPieceColor::WHITE) Index += 6;
	return TexturesPieces[Index - 1];
}


