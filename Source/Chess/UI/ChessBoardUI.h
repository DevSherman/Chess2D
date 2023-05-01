#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Math/Color.h"
#include "Chess/Chess.h"
#include "Chess/PController.h"
#include "ChessBoardUI.generated.h"

UCLASS()
class CHESS_API UChessBoardUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void AddToGrid(class UCBoxUI* _CBoxUI);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCursorPosition(FVector2D _Position);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCBoxUI> BP_CBoxUI;
	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> Pieces_Textures;

	UPROPERTY(EditAnywhere) FLinearColor WHITE_COLOR = FLinearColor(0.93333f, 0.93333f, 0.82353f);
	UPROPERTY(EditAnywhere) FLinearColor BLACK_COLOR = FLinearColor(0.46275f, 0.58824f, 0.33725f);
	UPROPERTY(EditAnywhere) FLinearColor SELECTION_COLOR = FLinearColor(0.72941f, 0.79216f, 0.26667f);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetCursorSprite(UTexture2D* _Texture);
	FORCEINLINE void SetController(class UMainController* _Controller) { Controller = _Controller; }
	FORCEINLINE class UCBoxUI* GetCBoxUI(FIntPoint _Coord) { return CBoxUIArray[_Coord.X][_Coord.Y]; }
	void OnMouseEnter(FIntPoint _Coord);

private:
	void SetCurrentCBoxUI(FIntPoint _Coord);
	void UpdateCBoxUI(EPieceType _Type, FIntPoint _Coord, bool bSpawn = false);
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	class UCBoxUI* CBoxUIArray[8][8];
	class UMainController* Controller;
	class UCBoxUI* CurrentCBoxUI = nullptr;
	bool bMouseIn = false;
};
