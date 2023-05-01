#pragma once

#include "CoreMinimal.h"
#include "CBox.h"

class CHESS_API ChessEngine
{

public:
	ChessEngine();
	void UpdateCBox(FIntPoint _Coord, CBox* _CBox);

private:
	CBox Grid[8][8];
};
