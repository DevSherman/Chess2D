#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Chess2D.h"
#include "CBoxUI.generated.h"


UCLASS()
class CHESS2D_API UCBoxUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Set(class UChessComponent& ChessComponent, FCCoord _Coord, FLinearColor Color, FLinearColor SelectionColor);
	inline FCCoord GetCoord() { return CCoord; }
	void SetPieceTexture(class UTexture2D* Texture);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* BackgroundImage;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* PieceImage;

private:
	class UChessComponent* ChessComponent;
	FLinearColor DefaultColor;
	FLinearColor SelectionColor;

	FCCoord CCoord;
};
