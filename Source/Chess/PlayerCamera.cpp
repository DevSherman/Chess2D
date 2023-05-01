#include "PlayerCamera.h"
#include "Camera/CameraComponent.h"
#include "PController.h"
#include "MainController.h"

#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

APlayerCamera::APlayerCamera()
{
	RootComponent = Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	MainController = CreateDefaultSubobject<UMainController>("Controller");
}

void APlayerCamera::BeginPlay()
{
	Super::BeginPlay();
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &APlayerCamera::LeftClickDown);
	PlayerInputComponent->BindAction("LeftClick", IE_Released, this, &APlayerCamera::LeftClickUp);
}

void APlayerCamera::LeftClickDown()
{
	MainController->OnMouseButtonDown(true);
}

void APlayerCamera::LeftClickUp()
{
	MainController->OnMouseButtonDown(false);
}


