#include "ChessBot.h"
#include "Utls.h"

inline void UChessBot::Init(UChessEngine& _Engine, int _Level, ETeam _Team)
{
	this->Engine = &_Engine;
	this->Level = _Level;
	this->Team = _Team;

	UE_LOG(LogTemp, Warning, TEXT("[UChessBot] Bot Started"));
}

FMovementResultArray UChessBot::GetRandomMove()
{
	FCoord coord = Engine->GetRandomPieceCoord(Team);
	ChessBoxData& data = *Engine->GetData(coord);
	FString pieceName = ChessUtls::GetStringData(&data);
	FString coordName = ChessUtls::GetCoordName(coord);

	FMovementResultArray result = Engine->GetMovementsFromData(data);
	if (!result.bIsValid) GetRandomMove();
	else
	{
		int finalMoveIndex = rand() % result.Movements.Num();
		FMovement mov = result.Movements[finalMoveIndex];
		ChessBoxData* Target = Engine->GetData(mov.Coord);

		if (Target)
		{
			Target->Update(result.Piece, result.Team);
			Engine->ClearBoard(result.CurrentCoord);

			result.FinalMoveIndex = finalMoveIndex;
			return result;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[UChessComponent::OpenentMove()] Data Error"));
			return FMovementResultArray();
		}
	}
	return FMovementResultArray();
}