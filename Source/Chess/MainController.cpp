#include "MainController.h"
#include "Utls.h"
#include "UI/ChessBoardUI.h"
#include "PController.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UMainController::UMainController()
{
	W_ChessBoardUI = Utls::LoadBlueprintFromPath<UChessBoardUI>("WidgetBlueprint'/Game/UI/W_ChessBoardUI.W_ChessBoardUI'");
}


void UMainController::BeginPlay()
{
	Super::BeginPlay();

	PController = Cast<APController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	ChessBoardUI = CreateWidget<UChessBoardUI>(GetWorld(), W_ChessBoardUI);
	ChessBoardUI->AddToViewport();
	ChessBoardUI->SetController(this);
	
}

void UMainController::UpdateCBox(FIntPoint _Coord, CBox* _CBox)
{
	Engine.UpdateCBox(_Coord, _CBox);
}

void UMainController::OnMouseButtonDown(bool bPressed)
{
	if (bPressed)
	{
		//ChessBoardUI->SetCursorSprite();

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("CLICK PRESSED: {%d-%d}"), CurrentCBoxSelected.X, CurrentCBoxSelected.Y));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("CLICK RELEASED: {%d-%d}"), CurrentCBoxSelected.X, CurrentCBoxSelected.Y));
	}
}

FVector2D UMainController::GetMousePosition()
{
	return FVector2D();
}

