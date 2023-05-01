#include "ChessGameModeBase.h"
#include "PlayerCamera.h"
#include "PController.h"

AChessGameModeBase::AChessGameModeBase()
{
	DefaultPawnClass = APlayerCamera::StaticClass();
	PlayerControllerClass = APController::StaticClass();
}
