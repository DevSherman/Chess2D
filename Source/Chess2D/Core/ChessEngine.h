#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ChessTypes.h"
#include "ChessEngine.generated.h"


UCLASS()
class CHESS2D_API UChessEngine : public UObject
{
	GENERATED_BODY()
	
public:
	UChessEngine();

	void UpdateBoard(ChessBoxData* Data);
	ChessBoxData& GetData(FCoord Coord);

private:
	ChessBoxData* Board[8][8];
};
