#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Core/ChessTypes.h"
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
	void SpawnPiece(EPieceType PieceType, EPieceColor PieceColor, int X, int Y);
	void UpdateBoard(ChessBoxData* Data);

	void OnClickPressed();
	void OnClickReleased();

private:
	UTexture2D* GetPieceTexture(EPieceType PieceType, EPieceColor PieceColor);
	void MoveToCursor();

protected:
	UPROPERTY(EditAnywhere) TSubclassOf<class UChessBoardUI> W_ChessBoardUI;
	UPROPERTY(EditAnywhere) TArray<UTexture2D*> TexturesPieces;

private:
	class UChessBoardUI* UI;
	class UCBoxUI* CBoxUIArray[8][8];
	class UCBoxUI* CurrentCBoxUI = nullptr;
	struct ChessBoxData* CurrentData = nullptr;

	class UChessEngine* Engine;
};
