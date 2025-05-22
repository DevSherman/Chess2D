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

	void UpdateBoard(ChessBoxData* Data, bool bInit = false);
	void ClearBoard(FCoord Coord);
	ChessBoxData* GetData(FCoord Coord) const;
	FMovementResultArray GetMovementsFromData(ChessBoxData& Data);
	int IsValidMovement(FCoord Coord);
	FString GetNotation(FMovementResultArray Result);
	FCoord GetRandomPieceCoord(ETeam Team) const;

private:
	ChessBoxData* Board[8][8];
	class UValidation* Validation;
	FString MovementRegistry;

};
