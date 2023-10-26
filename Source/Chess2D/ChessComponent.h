#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Chess2D.h"
#include "ChessComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHESS2D_API UChessComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UChessComponent();
	void CreateBoard();
	void RegistryCBoxUI(class UCBoxUI& CBoxUI);
	void SetCurrentCBoxUI(class UCBoxUI& CBoxUI);
	inline void ClearCurrentCBoxUI() { CurrentCBoxUI = nullptr; }
	void SpawnPiece(EPieceType PieceType, EColor PieceColor, int X, int Y);
	void UpdateCBoxData(EPieceType PieceType, EColor PieceColor, int X, int Y);


protected:
	UPROPERTY(EditAnywhere) TSubclassOf<class UChessBoardUI> W_ChessBoardUI;
	UPROPERTY(EditAnywhere) TArray<UTexture2D*> Pieces_Textures;

private:
	class UChessBoardUI* ChessBoardUI;
	class UCBoxUI* CBoxUIArray[8][8];
	class UCBoxUI* CurrentCBoxUI = nullptr;
	CBoxData* CBData[8][8];
};
