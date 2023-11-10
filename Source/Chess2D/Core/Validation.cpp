#include "Validation.h"
#include "ChessEngine.h"

void UValidation::Init(UChessEngine& _Engine)
{
	Engine = &_Engine;
}

TArray<FMovement> UValidation::GetMovements(ChessBoxData& Data)
{
	CurrentData = &Data;
	CurrentTeam = CurrentData->Team;
	X = CurrentData->Coord.X;
	Y = CurrentData->Coord.Y;
	PossibleMoves.Empty();
	Result.Empty();

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
	return Result;
}

int UValidation::IsValidMovement(FCoord Coord)
{
	for (size_t i = 0; i < Result.Num(); i++)
	{
		if (Result[i].Coord == Coord)
		{
			LastMove = Result[i];
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
			if (MoveData->PieceType == EPieceType::EMPTY) 
				Result.Add({ EMovementType::MOVE, PossibleMoves[i], CurrentTeam });
			else if(MoveData->Team != CurrentData->Team)
				Result.Add({ EMovementType::CAPTURE, PossibleMoves[i], CurrentTeam });
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
					Result.Add({ EMovementType::CASTLING, {2, 0}, CurrentTeam });
				}
			}
			ChessBoxData* RIGHT_ROOK = GetData({ 7, 0 });
			if (RIGHT_ROOK->PieceType == EPieceType::ROOK && !RIGHT_ROOK->bMoved)
			{
				if (GetData({ 5, 0 })->PieceType == EPieceType::EMPTY
					&& GetData({ 6, 0 })->PieceType == EPieceType::EMPTY)
				{
					Result.Add({ EMovementType::CASTLING, {6, 0}, CurrentTeam });
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
					Result.Add({ EMovementType::CASTLING, {2, 7}, CurrentTeam });
				}
			}
			ChessBoxData* RIGHT_ROOK = GetData({ 7, 7 });
			if (RIGHT_ROOK->PieceType == EPieceType::ROOK && !RIGHT_ROOK->bMoved)
			{
				if (GetData({ 5, 7 })->PieceType == EPieceType::EMPTY
					&& GetData({ 6, 7 })->PieceType == EPieceType::EMPTY)
				{
					Result.Add({ EMovementType::CASTLING, {6, 7}, CurrentTeam });
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

	if(Forward1 && Forward1->Team == ETeam::NONE) Result.Add({ EMovementType::MOVE, Forward1->Coord, Forward1->Team });
	if (Forward2 && Forward2->Team == ETeam::NONE) Result.Add({ EMovementType::MOVE, Forward2->Coord, Forward2->Team });
	if (LeftCapture && LeftCapture->Team != CurrentTeam && LeftCapture->Team != ETeam::NONE) Result.Add({ EMovementType::CAPTURE, LeftCapture->Coord, CurrentTeam });
	if (RightCapture && RightCapture->Team != CurrentTeam && RightCapture->Team != ETeam::NONE) Result.Add({ EMovementType::CAPTURE, RightCapture->Coord, CurrentTeam });
	//TODO: passant
	//CheckMoves();
}

void UValidation::GetAxisMovements()
{
	IterateAxis(1, 0);
	IterateAxis(0, 1);
	IterateAxis(1, 1);
	IterateAxis(-1, -1);
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

	if (Team == ETeam::WHITE)
	{
		int i = 1;
		while (true)
		{
			FCoord Coord = { W_KING_POS.X + i, W_KING_POS.Y + i };
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
			FCoord Coord = { W_KING_POS.X - i, W_KING_POS.Y - i };
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
			FCoord Coord = { W_KING_POS.X + i, W_KING_POS.Y - i };
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
			FCoord Coord = { W_KING_POS.X - i, W_KING_POS.Y + i };
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
	}

	return Coords;
}

