#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CBoxUI.generated.h"

UCLASS()
class CHESS_API UCBoxUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
		FIntPoint Coord;
	UPROPERTY(VisibleAnywhere)
		FString CoordName;

public:
	void Set(class UChessBoardUI* _ChessBoardUI, int32 _X, int32 _Y, FLinearColor _Color, FLinearColor _OutilneColor);

	UFUNCTION(BlueprintImplementableEvent) void SetColor(FLinearColor _Color);
	UFUNCTION(BlueprintImplementableEvent) void SetSprite(UTexture2D* _SpritePiece);
	UFUNCTION(BlueprintImplementableEvent) void ClearSprite();
	void UpdateSelection(bool bSelected);

private:

	FLinearColor DefaultColor;
	FLinearColor OutlineColor;

	class UChessBoardUI* ChessBoardUI;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	//virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
