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
	void SpawnPiece(EPieceType PieceType, ETeam PieceColor, int X, int Y);
	void UpdateBoard(ChessBoxData* Data);
	void ShowInfoPositions(TArray<EMovement> MovesArray);
	void ClearInfoPositions();
	void OnClickPressed();
	void OnClickReleased();

private:
	UTexture2D* GetPieceTexture(EPieceType PieceType, ETeam PieceColor);
	void MoveToCursor();
	void NextTeamTurn();
	void ResetPos();
	void Castling(FCoord Coord);

protected:
	UPROPERTY(EditAnywhere) TSubclassOf<class UChessBoardUI> W_ChessBoardUI;
	UPROPERTY(EditAnywhere) TArray<class UTexture2D*> PiecesTexture;

private:
	class UChessBoardUI* UI;
	class UCBoxUI* CBoxUIArray[8][8];
	class UCBoxUI* CurrentCBoxUI = nullptr;
	struct ChessBoxData* CurrentData = nullptr;

	class UChessEngine* Engine;
	TArray<EMovement> ValidMovements;
	ETeam CurrentTeam = ETeam::WHITE;

};
