#pragma once

#include "CoreMinimal.h"

const char COLUMN[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
const char ROW[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };

struct FCoord
{
	int X;
	int Y;
	FString Name;

	FString GetName()
	{
		if (Name.IsEmpty())
		{
			Name.AppendChar(COLUMN[X]);
			Name.AppendChar(ROW[Y]);
		}
		return Name;
	}
};

enum EPieceType
{
	EMPTY = 0,
	BISHOP = 1, //7
	KING = 2, //8
	KNIGHT = 3, //9
	PAWN = 4, //10
	QUEEN = 5, //11
	ROOK = 6 //12
};

enum EPieceColor
{
	NONE = 0,
	BLACK = 1,
	WHITE = 2
};

struct ChessBoxData
{
	ChessBoxData(int X, int Y)
	{
		PieceType = EPieceType::EMPTY;
		PieceColor = EPieceColor::NONE;
		Coord.X = X;
		Coord.Y = Y;
	}
	ChessBoxData(EPieceType _PieceType, EPieceColor _PieceColor, int X, int Y)
	{
		PieceType = _PieceType;
		PieceColor = _PieceColor;
		Coord.X = X;
		Coord.Y = Y;
	}

	void Update(EPieceType _PieceType, EPieceColor _PieceColor)
	{
		PieceType = _PieceType;
		PieceColor = _PieceColor;
	}

	EPieceType PieceType = EPieceType::EMPTY;
	EPieceColor PieceColor = EPieceColor::NONE;
	FCoord Coord{ -1, -1 };
};
