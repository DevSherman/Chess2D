#include "ChessEngine.h"

ChessEngine::ChessEngine()
{
	UE_LOG(LogClass, Warning, TEXT("[UChessEngine] - Init"));
}

void ChessEngine::UpdateCBox(FIntPoint _Coord, CBox* _CBox)
{

	Grid[_Coord.X][_Coord.Y] = *_CBox;
}
