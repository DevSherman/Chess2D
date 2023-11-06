#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Core/ChessTypes.h"
#include "CBoxUI.generated.h"


UCLASS()
class CHESS2D_API UCBoxUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Set(class UChessComponent& ChessComponent, FCoord _Coord, FLinearColor Color, FLinearColor SelectionColor);
	inline FCoord GetCoord() { return Coord; }
	void ShowSelection(bool bValue);
	void SetPieceTexture(class UTexture2D* Texture);
	void Clear();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* BackgroundImage; //-1
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* PieceImage; //0

private:
	class UChessComponent* ChessComponent;
	FLinearColor DefaultColor;
	FLinearColor SelectionColor;

	FCoord Coord;
};
