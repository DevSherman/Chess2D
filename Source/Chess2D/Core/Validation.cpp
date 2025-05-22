#include "Validation.h"
#include "ChessEngine.h"

void UValidation::Init(UChessEngine& _Engine)
{
	Engine = &_Engine;	
	CurrentPosition = EPositionResult::DEFAULT;
}

FMovementResultArray UValidation::GetMovements(ChessBoxData& Data)
{
	Result = FMovementResultArray();

	Result.Piece = Data.PieceType;
	Result.CurrentCoord = Data.Coord;
	Result.Team = Data.Team;

	CurrentData = &Data;
	CurrentTeam = CurrentData->Team;
	X = CurrentData->Coord.X;
	Y = CurrentData->Coord.Y;
	PossibleMoves.Empty();

	switch (CurrentData->PieceType)
	{
		case EMPTY: break;
		case BISHOP:GetBishopMovements(); break;
		case KING: GetKingMovements(); break;
		case KNIGHT: GetKnigthMovements(); break;
		case PAWN: GetPawnMovements(); break;
		case QUEEN: GetQueenMovements(); break;
		case ROOK: GetRookMovements(); break;
		default: break;
	}
	
	if (OnCheck(CurrentTeam).Num() > 0)
	{
		//if (CurrentTeam == ETeam::WHITE) CurrentPosition = EPositionResult::WHITE_ONCHECK;
		//if (CurrentTeam == ETeam::BLACK) CurrentPosition = EPositionResult::BLACK_ONCHECK;

		UE_LOG(LogTemp, Warning, TEXT("OnCheck"));
	}

	Result.bIsValid = Result.Movements.Num() > 0 ? true : false;

	/*if (!Result.bIsValid)
	{
		UE_LOG(LogTemp, Error, TEXT("[UValidation::GetMovements] Can't find any movement from the piece [xxx]."));
	}
	else UE_LOG(LogTemp, Warning, TEXT("[UValidation::GetMovements] The piece can move to: %i position/s"), Result.Movements.Num());*/

	return Result;
}

int UValidation::IsPlayerMoveValid(FCoord Coord)
{
	for (size_t i = 0; i < Result.Movements.Num(); i++)
	{
		if (Result.Movements[i].Coord == Coord)
		{
			LastMove = Result.Movements[i];
			return i;
		}
	}
	return -1;
}

void UValidation::UpdateKingPos(ETeam Team, FCoord Pos)
{
	if (Team == ETeam::WHITE) W_KING_POS = Pos;
	else if (Team == ETeam::BLACK) B_KING_POS = Pos;
}

void UValidation::CheckMoves()
{
	for (int i = 0; i < PossibleMoves.Num(); i++)
	{
		ChessBoxData* MoveData = Engine->GetData(PossibleMoves[i]);
		if (MoveData)
		{
			if (MoveData->PieceType == EPieceType::EMPTY) AddToResult(EMovementType::MOVE, PossibleMoves[i]);
			else if(MoveData->Team != CurrentTeam) AddToResult(EMovementType::CAPTURE, PossibleMoves[i]);
		}
	}
}
ChessBoxData* UValidation::GetData(FCoord Coord)
{
	return Engine->GetData(Coord);
}

void UValidation::GetKnigthMovements()
{
	PossibleMoves =
	{
		{X - 1, Y + 2}, {X + 1, Y + 2},
		{X - 1, Y - 2}, {X + 1, Y - 2},
		{X - 2, Y + 1}, {X + 2, Y + 1},
		{X - 2, Y - 1}, {X + 2, Y - 1}
	};
	CheckMoves();
}
void UValidation::GetBishopMovements()
{
	GetDiagonalMovements();
	CheckMoves();
}
void UValidation::GetKingMovements()
{
	PossibleMoves =
	{
		{X - 1, Y + 1}, {X, Y + 1}, {X + 1, Y + 1},
		{X - 1, Y}, {X + 1, Y },
		{X - 1, Y - 1}, {X, Y - 1}, {X + 1, Y - 1},
	};

	if (CurrentTeam == ETeam::WHITE)
	{
		ChessBoxData* WHITE_KING = GetData({ 4, 0 });
		//TODO: check color?
		if (WHITE_KING->PieceType == EPieceType::KING && !WHITE_KING->bMoved)
		{
			ChessBoxData* LEFT_ROOK = GetData({ 0, 0 });
			if (LEFT_ROOK->PieceType == EPieceType::ROOK && !LEFT_ROOK->bMoved)
			{
				if(GetData({ 1, 0 })->PieceType == EPieceType::EMPTY
					&& GetData({ 2, 0 })->PieceType == EPieceType::EMPTY
					&& GetData({ 3, 0 })->PieceType == EPieceType::EMPTY)
				{
					AddToResult(EMovementType::L_CASTLING, {2, 0});
				}
			}
			ChessBoxData* RIGHT_ROOK = GetData({ 7, 0 });
			if (RIGHT_ROOK->PieceType == EPieceType::ROOK && !RIGHT_ROOK->bMoved)
			{
				if (GetData({ 5, 0 })->PieceType == EPieceType::EMPTY
					&& GetData({ 6, 0 })->PieceType == EPieceType::EMPTY)
				{
					AddToResult(EMovementType::S_CASTLING, {6, 0});
				}
			}
		}
	}
	else if (CurrentTeam == ETeam::BLACK)
	{
		ChessBoxData* WHITE_KING = GetData({ 4, 7 });
		//TODO: check color?
		if (WHITE_KING->PieceType == EPieceType::KING && !WHITE_KING->bMoved)
		{
			ChessBoxData* LEFT_ROOK = GetData({ 0, 7 });
			if (LEFT_ROOK->PieceType == EPieceType::ROOK && !LEFT_ROOK->bMoved)
			{
				if (GetData({ 1, 7 })->PieceType == EPieceType::EMPTY
					&& GetData({ 2, 7 })->PieceType == EPieceType::EMPTY
					&& GetData({ 3, 7})->PieceType == EPieceType::EMPTY)
				{
					AddToResult(EMovementType::L_CASTLING, {2, 7});
				}
			}
			ChessBoxData* RIGHT_ROOK = GetData({ 7, 7 });
			if (RIGHT_ROOK->PieceType == EPieceType::ROOK && !RIGHT_ROOK->bMoved)
			{
				if (GetData({ 5, 7 })->PieceType == EPieceType::EMPTY
					&& GetData({ 6, 7 })->PieceType == EPieceType::EMPTY)
				{
					AddToResult(EMovementType::S_CASTLING, {6, 7});
				}
			}
		}
	}


	CheckMoves();
}
void UValidation::GetQueenMovements()
{
	GetDiagonalMovements();
	GetAxisMovements();
	CheckMoves();
}
void UValidation::GetRookMovements()
{
	GetAxisMovements();
	CheckMoves();
}
void UValidation::GetPawnMovements()
{
	ChessBoxData* Forward1 = nullptr;
	ChessBoxData* Forward2 = nullptr;
	ChessBoxData* LeftCapture = nullptr;
	ChessBoxData* RightCapture = nullptr;

	if (CurrentTeam == ETeam::WHITE)
	{
		Forward1 = GetData({ X, Y + 1 });
		if (Y == 1) Forward2 = GetData({ X, Y + 2 });
		LeftCapture = GetData({ X - 1, Y + 1 });
		RightCapture = GetData({ X + 1, Y + 1 });
	}
	else if (CurrentTeam == ETeam::BLACK)
	{
		Forward1 = GetData({ X, Y - 1 });
		Forward2 = GetData({ X, Y - 2 });
		LeftCapture = GetData({ X - 1, Y - 1 });
		RightCapture = GetData({ X + 1, Y - 1 });
	}

	if (Forward1 && Forward1->Team == ETeam::NONE)
	{
		AddToResult(EMovementType::MOVE, Forward1->Coord);
		if (Forward2 && Forward2->Team == ETeam::NONE) AddToResult(EMovementType::MOVE, Forward2->Coord);
	}
	if (LeftCapture && LeftCapture->Team != CurrentTeam && LeftCapture->Team != ETeam::NONE) AddToResult(EMovementType::CAPTURE, LeftCapture->Coord);
	if (RightCapture && RightCapture->Team != CurrentTeam && RightCapture->Team != ETeam::NONE) AddToResult(EMovementType::CAPTURE, RightCapture->Coord);
	//TODO: passant
	//CheckMoves();
}

void UValidation::GetAxisMovements()
{
	IterateAxis(1, 0);
	IterateAxis(0, 1);
	IterateAxis(-1, 0);
	IterateAxis(0, -1);
}

void UValidation::GetDiagonalMovements()
{
	IterateAxis(1, 1);
	IterateAxis(1, -1);
	IterateAxis(-1, 1);
	IterateAxis(-1, -1);
}

void UValidation::IterateAxis(int IncrementX, int IncrementY)
{
	FCoord Coord = { X + IncrementX, Y + IncrementY };
	while (true)
	{
		ChessBoxData* Data = GetData({ Coord });
		if (!Data) break;

		if (Data->Team == ETeam::NONE) PossibleMoves.Add(Coord);
		else if ((Data->Team != CurrentTeam)) { PossibleMoves.Add(Coord); break; }
		else break;

		Coord.X += IncrementX;
		Coord.Y += IncrementY;
	}
}

TArray<FCoord> UValidation::OnCheck(ETeam Team)
{
	TArray<FCoord> Coords;
	ChessBoxData* Data;

	FCoord KING_POS = (Team == ETeam::WHITE) ? W_KING_POS : B_KING_POS;



	//Queen & bishop positions
	int i = 1;
	while (true)
	{
		FCoord Coord = { KING_POS.X + i, KING_POS.Y + i };
		Data = GetData({ Coord });
		if (!Data) break;

		if (Data->Team == Team) break;
		else if (Data->Team != Team && Data->Team != ETeam::NONE)
		{
			if (Data->PieceType == EPieceType::BISHOP || Data->PieceType == EPieceType::QUEEN) Coords.Add(Coord);
			break;
		}
		i++;
	}
	i = 1;
	while (true)
	{
		FCoord Coord = { KING_POS.X - i, KING_POS.Y - i };
		Data = GetData({ Coord });
		if (!Data) break;

		if (Data->Team == Team) break;
		else if (Data->Team != Team && Data->Team != ETeam::NONE)
		{
			if (Data->PieceType == EPieceType::BISHOP || Data->PieceType == EPieceType::QUEEN) Coords.Add(Coord);
			break;
		}
		i++;
	}
	i = 1;
	while (true)
	{
		FCoord Coord = { KING_POS.X + i, KING_POS.Y - i };
		Data = GetData({ Coord });
		if (!Data) break;

		if (Data->Team == Team) break;
		else if (Data->Team != Team)
		{
			if (Data->PieceType == EPieceType::BISHOP || Data->PieceType == EPieceType::QUEEN) Coords.Add(Coord);
			break;
		}
		i++;
	}
	i = 1;
	while (true)
	{
		FCoord Coord = { KING_POS.X - i, KING_POS.Y + i };
		Data = GetData({ Coord });
		if (!Data) break;

		if (Data->Team == CurrentTeam) break;
		else if ((Data->Team != CurrentTeam))
		{
			if (Data->PieceType == EPieceType::BISHOP || Data->PieceType == EPieceType::QUEEN) Coords.Add(Coord);
			break;
		}
		i++;
	}
	//knight positions
	TArray<FCoord> Knights_Pos = 
	{
		{ KING_POS.X + 1, KING_POS.Y + 2 },
		{ KING_POS.X - 1, KING_POS.Y + 2 },

		{ KING_POS.X + 1, KING_POS.Y - 2 },
		{ KING_POS.X - 1, KING_POS.Y - 2 },

		{ KING_POS.X + 2, KING_POS.Y + 1 },
		{ KING_POS.X + 2, KING_POS.Y - 1 },

		{ KING_POS.X - 2, KING_POS.Y + 1 },
		{ KING_POS.X - 2, KING_POS.Y - 1 }
	};

	ETeam OpenentTeam = (Team == ETeam::WHITE) ? ETeam::BLACK : ETeam::WHITE;

	for (int k = 0; k < Knights_Pos.Num() - 1; k++)
		if (HasPieceType(Knights_Pos[k], EPieceType::KNIGHT, OpenentTeam)) Coords.Add(Knights_Pos[k]);

	return Coords;
}

bool UValidation::HasPieceType(FCoord Coord, EPieceType Piece, ETeam Team)
{
	ChessBoxData* Data = GetData(Coord);
	if (Data && Data->Team == Team && Data->PieceType == Piece) return true;
	return false;
}

void UValidation::AddToResult(EMovementType MovType, FCoord Coord)
{
	Result.Movements.Add({ MovType , Coord });
}

