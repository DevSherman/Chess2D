#include "Chess2DGameModeBase.h"

#include "PlayerCamera.h"

AChess2DGameModeBase::AChess2DGameModeBase()
{
	DefaultPawnClass = APlayerCamera::StaticClass();
}