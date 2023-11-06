#include "PlayerCamera.h"

#include "Camera/CameraComponent.h"
#include "ChessComponent.h"
#include "GameFramework/PlayerController.h"
#include <Kismet/GameplayStatics.h>

APlayerCamera::APlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	ChessComponent = CreateDefaultSubobject<UChessComponent>(TEXT("ChessComponent"));
}

void APlayerCamera::BeginPlay()
{
	Super::BeginPlay();
	ChessComponent->CreateBoard();

	Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!Controller)
	{
		UE_LOG(LogTemp, Error, TEXT("Error to set PlayerController"));
		return;
	}
	Controller->SetInputMode(FInputModeUIOnly());
	Controller->bShowMouseCursor = true;
	Controller->bEnableClickEvents = true;
	Controller->bEnableMouseOverEvents = true;
	Controller->CurrentMouseCursor = EMouseCursor::GrabHand;
}

/*void APlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

