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
	TArray<EMovement> GetMovements(ChessBoxData& Data);
	int IsValidMovement(FCoord Coord);

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

private:
	UChessEngine* Engine;
	EMovement LastMove;
	TArray<FCoord> PossibleMoves;
	TArray<EMovement> Result;
	ChessBoxData* CurrentData;
	ETeam CurrentTeam;
	int X, Y;
};
