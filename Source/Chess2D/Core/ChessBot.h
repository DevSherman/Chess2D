#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ChessTypes.h"
#include "ChessEngine.h"
#include "ChessBot.generated.h"


UCLASS()
class CHESS2D_API UChessBot : public UObject
{
	GENERATED_BODY()

public:
	inline void Init(UChessEngine& _Engine, int BotLevel, ETeam BotTeam);

	inline void SetDifficult(int _Level) { this->Level = _Level; }
	inline void SetTeam(ETeam _Team) { this->Team = _Team; }

public:
	virtual FMovementResultArray GetRandomMove();


private:
	UChessEngine* Engine;
	int Level = 0;
	ETeam Team = ETeam::BLACK;
};
