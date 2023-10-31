#pragma once

#include "CoreMinimal.h"
#include "ChessTypes.h"

namespace ChessUtls
{
	static FString GetStringData(ChessBoxData* Data)
	{
		FString Name;
		if (Data->PieceColor == EPieceColor::WHITE) Name = "WHITE";
		if (Data->PieceColor == EPieceColor::BLACK) Name = "BLACK";

		if (Data->PieceType == EPieceType::BISHOP) Name += "_BISHOP";
		if (Data->PieceType == EPieceType::KING) Name += "_KING";
		if (Data->PieceType == EPieceType::KNIGHT) Name += "_KNIGHT";
		if (Data->PieceType == EPieceType::PAWN) Name += "_PAWN";
		if (Data->PieceType == EPieceType::QUEEN) Name += "_QUEEN";
		if (Data->PieceType == EPieceType::ROOK) Name += "_ROOK";

		return Name;
	}
}