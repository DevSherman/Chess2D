#pragma once

#include "CoreMinimal.h"
#include "../Chess.h"

class CHESS_API CBox
{
public:
	FORCEINLINE CBox(EPieceType _PieceType = EPieceType::EMPTY) { PieceType = _PieceType; }
	EPieceType PieceType = EPieceType::EMPTY;

protected:

	FORCEINLINE EColor GetColor() { return PieceType >= 6 ? EColor::BLACK : EColor::WHITE; }
	FORCEINLINE void Clear() { PieceType = EPieceType::EMPTY; }
};
