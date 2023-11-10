#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ChessTypes.h"
#include "Validation.generated.h"

UCLASS()
class CHESS2D_API UValidation : public UObject
{
	GENERATED_BODY()

public:
	void Init(class UChessEngine& _Engine);
	TArray<FMovement> GetMovements(ChessBoxData& Data);
	int IsValidMovement(FCoord Coord);
	void UpdateKingPos(ETeam Team, FCoord Pos);

private:
	void CheckMoves();
	ChessBoxData* GetData(FCoord Coord);

	void GetKnigthMovements();
	void GetBishopMovements();
	void GetKingMovements();
	void GetQueenMovements();
	void GetRookMovements();
	void GetPawnMovements();

	void GetAxisMovements();
	void GetDiagonalMovements();
	void IterateAxis(int IncrementX, int IncrementY);

	TArray<FCoord> OnCheck(ETeam Team);

private:
	UChessEngine* Engine;
	FMovement LastMove;
	TArray<FCoord> PossibleMoves;
	TArray<FMovement> Result;
	ChessBoxData* CurrentData;
	ETeam CurrentTeam;
	int X, Y;
	FCoord W_KING_POS = {0, 4};
	FCoord B_KING_POS = {7, 4};
};
