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
	FMovementResultArray GetMovements(ChessBoxData& Data);
	int IsPlayerMoveValid(FCoord Coord);
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
	bool HasPieceType(FCoord Coord, EPieceType Piece, ETeam Team);
	void AddToResult(EMovementType MovType, FCoord Coord);

private:
	UChessEngine* Engine;
	EPositionResult CurrentPosition;
	FMovement LastMove;
	TArray<FCoord> PossibleMoves;
	FMovementResultArray Result;
	ChessBoxData* CurrentData;
	ETeam CurrentTeam;
	int X, Y;
	FCoord W_KING_POS = {0, 4};
	FCoord B_KING_POS = {7, 4};
};
