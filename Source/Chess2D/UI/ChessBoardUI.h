#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChessBoardUI.generated.h"


UCLASS()
class CHESS2D_API UChessBoardUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(class UChessComponent& ChessComponent);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere) TSubclassOf<class UCBoxUI> W_CBoxUI;
	UPROPERTY(EditAnywhere) FLinearColor WHITE_COLOR = FLinearColor(0.93333f, 0.93333f, 0.82353f);
	UPROPERTY(EditAnywhere) FLinearColor BLACK_COLOR = FLinearColor(0.46275f, 0.58824f, 0.33725f);
	UPROPERTY(EditAnywhere) FLinearColor SELECTION_COLOR = FLinearColor(0.72941f, 0.79216f, 0.26667f);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UWrapBox* ChessBoardBox;

private:
	class UChessComponent* ChessComponent;
	class APlayerController* Controller;
};
