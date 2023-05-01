#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Core/ChessEngine.h"
#include "MainController.generated.h"

UCLASS()
class CHESS_API UMainController : public USceneComponent
{
	GENERATED_BODY()

public:	
	UMainController();

	FORCEINLINE void SetCurrentCBox(FIntPoint _Current) { CurrentCBoxSelected = _Current; }
	void UpdateCBox(FIntPoint _Coord, class CBox* _CBox);
	void OnMouseButtonDown(bool bPressed);
	FVector2D GetMousePosition();

protected:
	virtual void BeginPlay() override;

	class UChessBoardUI* ChessBoardUI;
	UPROPERTY(VisibleAnywhere) TSubclassOf<class UChessBoardUI> W_ChessBoardUI;

private:
	class APController* PController;
	ChessEngine Engine{};
	FIntPoint CurrentCBoxSelected;
};
