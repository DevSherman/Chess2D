#include "ChessEngine.h"
#include "Validation.h"
#include "Utls.h"

UChessEngine::UChessEngine()
{
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
			Board[x][y] = new ChessBoxData(x, y);

	Validation = NewObject<UValidation>();
	Validation->Init(*this);

	UE_LOG(LogTemp, Warning, TEXT("[UChessEngine] Engine started."));
}
void UChessEngine::UpdateBoard(ChessBoxData* Data, bool bInit)
{
	if(!bInit) Data->bMoved = true;
	Board[Data->Coord.X][Data->Coord.Y] = Data;

	if (Data->PieceType == EPieceType::KING) Validation->UpdateKingPos(Data->Team, Data->Coord);

	UE_LOG
	(
		LogTemp, Warning,
		TEXT("[UChessEngine] UpdateBoard in coord: %s with data: %s"),
		*ChessUtls::GetCoordName(Data->Coord), *ChessUtls::GetStringData(Data)
	);
}

void UChessEngine::ClearBoard(FCoord Coord)
{
	Board[Coord.X][Coord.Y] = new ChessBoxData(Coord.X, Coord.Y);
}

ChessBoxData* UChessEngine::GetData(FCoord Coord)
{
	if ((Coord.X < 0 || Coord.X > 7 || Coord.Y < 0 || Coord.Y > 7)) return nullptr;
	return Board[Coord.X][Coord.Y];
}

TArray<FMovement> UChessEngine::GetMovements(ChessBoxData& Data)
{
	return Validation->GetMovements(Data);
}

int UChessEngine::IsValidMovement(FCoord Coord)
{
	return Validation->IsValidMovement(Coord);
}


