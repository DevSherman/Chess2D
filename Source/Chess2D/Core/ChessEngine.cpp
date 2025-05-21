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

	FString MovementName = ChessUtls::GetPieceCharName(Data->PieceType) + ChessUtls::GetCoordName(Data->Coord);
	UE_LOG(LogTemp, Warning, TEXT("[UChessEngine::UpdateBoard]: %s"), *MovementName);

	if (Data->PieceType == EPieceType::KING) Validation->UpdateKingPos(Data->Team, Data->Coord);
}

void UChessEngine::ClearBoard(FCoord Coord)
{
	Board[Coord.X][Coord.Y] = new ChessBoxData(Coord.X, Coord.Y);
}

ChessBoxData* UChessEngine::GetData(FCoord Coord) const
{
	if ((Coord.X < 0 || Coord.X > 7 || Coord.Y < 0 || Coord.Y > 7)) return nullptr;
	return Board[Coord.X][Coord.Y];
}

FMovementResultArray UChessEngine::GetMovementsFromData(ChessBoxData& Data)
{
	return Validation->GetMovements(Data);
}

int UChessEngine::IsValidMovement(FCoord Coord)
{
	return Validation->IsPlayerMoveValid(Coord);
}

FCoord UChessEngine::GetRandomPieceCoord(ETeam Team) const
{
	TArray<FCoord> PiecesCoord;

	for (size_t x = 0; x < 8; x++)
		for (size_t y = 0; y < 8; y++)
			if (Board[x][y]->Team == Team) PiecesCoord.Add(Board[x][y]->Coord);

	//TODO: check finished game

	return PiecesCoord[rand() % PiecesCoord.Num()];
}


