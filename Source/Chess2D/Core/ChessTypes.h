#pragma once

#include "CoreMinimal.h"

const char COLUMN[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
const char ROW[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };

const char english_anotation[6] = {'B', 'K', 'N', ' ', 'Q', 'R'};
const char spanish_anotation[6] = {'A', 'R', 'C', ' ', 'D', 'T'};


struct FCoord
{
	int X;
	int Y;

	bool operator==(FCoord const& other)
	{
		return (X == other.X && Y == other.Y);
	}
	bool operator!=(FCoord const& other)
	{
		return (X != other.X || Y != other.Y);
	}
};

enum EPieceType
{
	EMPTY,// = 0,
	BISHOP,// = 1, //7
	KING,// = 2, //8
	KNIGHT,// = 3, //9
	PAWN,// = 4, //10
	QUEEN, // = 5, //11
	ROOK// = 6 //12
};

enum ETeam
{
	NONE,
	BLACK,
	WHITE
};

enum EMovementType
{
	MOVE,
	CAPTURE,
	PASSANT,
	CASTLING
};

struct FMovement
{
	EMovementType Type;
	FCoord Coord;
	ETeam Team;
};

enum EInfoType
{
	CLEAR_TYPE,
	MOVE_TYPE,
	CAPTURE_TYPE
};

struct FCheck
{
	bool bValue = false;
	FCoord Coords[2];
};

struct ChessBoxData
{
	ChessBoxData(int X, int Y)
	{
		PieceType = EPieceType::EMPTY;
		Team = ETeam::NONE;
		Coord.X = X;
		Coord.Y = Y;
		bMoved = false;
	}
	ChessBoxData(EPieceType _PieceType, ETeam _Team, int X, int Y)
	{
		PieceType = _PieceType;
		Team = _Team;
		Coord.X = X;
		Coord.Y = Y;
	}

	void Update(EPieceType _PieceType, ETeam _Team)
	{
		PieceType = _PieceType;
		Team = _Team;
	}

	EPieceType PieceType = EPieceType::EMPTY;
	ETeam Team = ETeam::NONE;
	FCoord Coord{ -1, -1 };
	bool bMoved = false;
};

