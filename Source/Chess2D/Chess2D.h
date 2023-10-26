#pragma once

#include "CoreMinimal.h"
#include "Chess2D.h"

const char ROW[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };
const char COLUMN[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

struct FCCoord
{
	int X;
	int Y;
	FString Name;
};

enum EPieceType
{
	BLACK_BISHOP = 0,
	BLACK_KING = 1,
	BLACK_KNIGHT = 2,
	BLACK_PAWN = 3,
	BLACK_QUEEN = 4,
	BLACK_ROOK = 5,
	WHITE_BISHOP = 6,
	WHITE_KING = 7,
	WHITE_KNIGHT = 8,
	WHITE_PAWN = 9,
	WHITE_QUEEN = 10,
	WHITE_ROOK = 11,
	EMPTY = 12
};

enum EColor
{
	WHITE,
	BLACK,
	NONE
};

struct CBoxData
{
	CBoxData(EPieceType _PieceType, EColor _PieceColor)
	{
		PieceType = _PieceType;
		PieceColor = _PieceColor;
	}
	EPieceType PieceType;
	EColor PieceColor;
};