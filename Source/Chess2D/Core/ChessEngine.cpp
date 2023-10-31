#include "ChessEngine.h"
#include "Utls.h"

UChessEngine::UChessEngine()
{
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
			Board[x][y] = new ChessBoxData(x, y);

	UE_LOG(LogTemp, Warning, TEXT("[UChessEngine] Engine started."));

}
void UChessEngine::UpdateBoard(ChessBoxData* Data)
{
	Board[Data->Coord.X][Data->Coord.Y] = Data;
	UE_LOG
	(
		LogTemp, Warning,
		TEXT("[UChessEngine] UpdateBoard in coord: %s with data: %s"),
		*Data->Coord.GetName(), *ChessUtls::GetStringData(Data)
	);
}

ChessBoxData& UChessEngine::GetData(FCoord Coord)
{
	return *Board[Coord.X][Coord.Y];
}


