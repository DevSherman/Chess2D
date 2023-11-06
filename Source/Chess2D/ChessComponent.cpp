#include "ChessComponent.h"
#include "Core/ChessEngine.h"
#include "UI/ChessBoardUI.h"
#include "UI/CBoxUI.h"
#include "Core/ChessTypes.h"
#include "Utls.h"
#include "Core/Utls.h"

UChessComponent::UChessComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Engine = NewObject<UChessEngine>();
}

void UChessComponent::CreateBoard()
{
	PiecesTexture = Utls::LoadTexturesFromPath("/Game/Textures/Pieces/");

	W_ChessBoardUI = Utls::LoadBlueprintFromPath<UChessBoardUI>("'/Game/Widgets/W_ChessBoardUI.W_ChessBoardUI'");
	UI = CreateWidget<UChessBoardUI>(GetWorld(), W_ChessBoardUI);
	if (!UI) { UE_LOG(LogTemp, Error, TEXT("[UChessComponent: %s] UI not initilizaed.")); return; }



	UI->AddToViewport();
	UI->Init(*this);

	UE_LOG(LogTemp, Warning, TEXT("[UChessComponent] Board Created."));

	SpawnPiece(EPieceType::ROOK, ETeam::WHITE, 0, 0);
	SpawnPiece(EPieceType::KNIGHT, ETeam::WHITE, 1, 0);
	SpawnPiece(EPieceType::BISHOP, ETeam::WHITE, 2, 0);
	SpawnPiece(EPieceType::QUEEN, ETeam::WHITE, 3, 0);
	SpawnPiece(EPieceType::KING, ETeam::WHITE, 4, 0);
	SpawnPiece(EPieceType::BISHOP, ETeam::WHITE, 5, 0);
	SpawnPiece(EPieceType::KNIGHT, ETeam::WHITE, 6, 0);
	SpawnPiece(EPieceType::ROOK, ETeam::WHITE, 7, 0);

	SpawnPiece(EPieceType::PAWN, ETeam::WHITE, 0, 1);
	SpawnPiece(EPieceType::PAWN, ETeam::WHITE, 1, 1);
	SpawnPiece(EPieceType::PAWN, ETeam::WHITE, 2, 1);
	SpawnPiece(EPieceType::PAWN, ETeam::WHITE, 3, 1);
	SpawnPiece(EPieceType::PAWN, ETeam::WHITE, 4, 1);
	SpawnPiece(EPieceType::PAWN, ETeam::WHITE, 5, 1);
	SpawnPiece(EPieceType::PAWN, ETeam::WHITE, 6, 1);
	SpawnPiece(EPieceType::PAWN, ETeam::WHITE, 7, 1);

	SpawnPiece(EPieceType::ROOK, ETeam::BLACK, 0, 7);
	SpawnPiece(EPieceType::KNIGHT, ETeam::BLACK, 1, 7);
	SpawnPiece(EPieceType::BISHOP, ETeam::BLACK, 2, 7);
	SpawnPiece(EPieceType::QUEEN, ETeam::BLACK, 3, 7);
	SpawnPiece(EPieceType::KING, ETeam::BLACK, 4, 7);
	SpawnPiece(EPieceType::BISHOP, ETeam::BLACK, 5, 7);
	SpawnPiece(EPieceType::KNIGHT, ETeam::BLACK, 6, 7);
	SpawnPiece(EPieceType::ROOK, ETeam::BLACK, 7, 7);

	SpawnPiece(EPieceType::PAWN, ETeam::BLACK, 0, 6);
	SpawnPiece(EPieceType::PAWN, ETeam::BLACK, 1, 6);
	SpawnPiece(EPieceType::PAWN, ETeam::BLACK, 2, 6);
	SpawnPiece(EPieceType::PAWN, ETeam::BLACK, 3, 6);
	SpawnPiece(EPieceType::PAWN, ETeam::BLACK, 4, 6);
	SpawnPiece(EPieceType::PAWN, ETeam::BLACK, 5, 6);
	SpawnPiece(EPieceType::PAWN, ETeam::BLACK, 6, 6);
	SpawnPiece(EPieceType::PAWN, ETeam::BLACK, 7, 6);

	UE_LOG(LogTemp, Warning, TEXT("[UChessComponent] Pieces placed."));
}

void UChessComponent::RegistryCBoxUI(UCBoxUI& CBoxUI)
{
	int X = CBoxUI.GetCoord().X;
	int Y = CBoxUI.GetCoord().Y;

	CBoxUIArray[X][Y] = &CBoxUI;
}

void UChessComponent::SetCurrentCBoxUI(UCBoxUI& CBoxUI)
{
	CurrentCBoxUI = &CBoxUI;
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("CurrentCBoxUI: [%s]"), *CurrentCBoxUI->GetCoord().GetName()));
}

void UChessComponent::UpdateBoard(ChessBoxData* Data)
{
	Engine->UpdateBoard(Data);
}

void UChessComponent::ShowInfoPositions(TArray<EMovement> MovesArray)
{
	for (int i = 0; i < ValidMovements.Num(); i++)
		CBoxUIArray[ValidMovements[i].Coord.X][ValidMovements[i].Coord.Y]->ShowSelection(true);
}
void UChessComponent::ClearInfoPositions()
{
	for (int i = 0; i < ValidMovements.Num(); i++)
		CBoxUIArray[ValidMovements[i].Coord.X][ValidMovements[i].Coord.Y]->ShowSelection(false);
	ValidMovements.Empty();
}

void UChessComponent::OnClickPressed()
{
	if (!CurrentCBoxUI) return;

	MoveToCursor();
}

void UChessComponent::MoveToCursor()
{
	CurrentData = Engine->GetData(CurrentCBoxUI->GetCoord());
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("CurrentData: [%s]"), *ChessUtls::GetCoordName(CurrentData->Coord)));

	ValidMovements = Engine->GetMovements(*CurrentData);
	if (ValidMovements.Num() == 0) return;

	Engine->ClearBoard(CurrentCBoxUI->GetCoord());
	UI->SetCursorImage(GetPieceTexture(CurrentData->PieceType, CurrentData->Team));
	ShowInfoPositions(ValidMovements);
	CurrentCBoxUI->Clear();

	//for (int i = 0; i < ValidMovements.Num(); i++)
		//UE_LOG(LogTemp, Warning, TEXT("ValidMovements: %s"), *ChessUtls::GetCoordName(ValidMovements[i].Coord));
}

void UChessComponent::OnClickReleased()
{
	if (ValidMovements.Num() == 0) return;

	if (CurrentData) //mouse slot data
	{
		if (CurrentCBoxUI) //move
		{
			int Index = Engine->IsValidMovement(CurrentCBoxUI->GetCoord());
			if (Index > -1)
			{
				EMovement Move = ValidMovements[Index];

				switch (Move.Type)
				{
					case MovementType::MOVE:
					{

						break;
					}
					case MovementType::CAPTURE:
					{

						break;
					}
					case MovementType::CASTLING:
					{
						Castling(Move.Coord);
						break;
					}
				}

				CurrentCBoxUI->SetPieceTexture(UI->GetImageFromCursor());
				CurrentData->Coord = CurrentCBoxUI->GetCoord();
				Engine->UpdateBoard(CurrentData);
				NextTeamTurn();
			}
			else ResetPos();
		}
	}

	ClearInfoPositions();
	UI->ClearCursor();
	CurrentData = nullptr;
}

void UChessComponent::NextTeamTurn()
{
	if (CurrentTeam == ETeam::BLACK) CurrentTeam = ETeam::WHITE;
	else if(CurrentTeam == ETeam::WHITE) CurrentTeam = ETeam::BLACK;
	UE_LOG(LogTemp, Warning, TEXT("[UChessComponent] Next Turn."));
}

void UChessComponent::ResetPos()
{
	CBoxUIArray[CurrentData->Coord.X][CurrentData->Coord.Y]->SetPieceTexture(UI->GetImageFromCursor());
	Engine->UpdateBoard(CurrentData);
}

void UChessComponent::Castling(FCoord Coord)
{
	//rook movement

	if (Coord == FCoord{ 2, 0 }) //castling white left
	{
		ChessBoxData* Rook = Engine->GetData({ 0, 0 });
		CBoxUIArray[3][0]->SetPieceTexture(GetPieceTexture(Rook->PieceType, Rook->Team));

		Rook->Coord = { 3, 0 };
		Engine->UpdateBoard(Rook);

		CBoxUIArray[0][0]->Clear();
		Engine->ClearBoard({ 0, 0 });
	}
	else if (Coord == FCoord{ 6, 0 }) //castling white right
	{
		ChessBoxData* Rook = Engine->GetData({ 7, 0 });
		CBoxUIArray[5][0]->SetPieceTexture(GetPieceTexture(Rook->PieceType, Rook->Team));
		Rook->Coord = { 5, 0 };
		Engine->UpdateBoard(Rook);

		CBoxUIArray[7][0]->Clear();
		Engine->ClearBoard({ 7, 0 });
	}
	else if (Coord == FCoord{ 2, 7 }) //castling black right
	{
		ChessBoxData* Rook = Engine->GetData({ 0, 7 });
		CBoxUIArray[3][7]->SetPieceTexture(GetPieceTexture(Rook->PieceType, Rook->Team));
		Rook->Coord = { 3, 7 };
		Engine->UpdateBoard(Rook);

		CBoxUIArray[0][7]->Clear();
		Engine->ClearBoard({ 0, 7 });
	}
	else if (Coord == FCoord{ 6, 7 }) //castling white left
	{
		ChessBoxData* Rook = Engine->GetData({ 7, 7 });
		CBoxUIArray[5][7]->SetPieceTexture(GetPieceTexture(Rook->PieceType, Rook->Team));
		Rook->Coord = { 5, 7 };
		Engine->UpdateBoard(Rook);

		CBoxUIArray[7][7]->Clear();
		Engine->ClearBoard({ 7, 7 });
	}
}

void UChessComponent::SpawnPiece(EPieceType PieceType, ETeam PieceColor, int X, int Y)
{
	Engine->UpdateBoard(new ChessBoxData(PieceType, PieceColor, X, Y), true);
	CBoxUIArray[X][Y]->SetPieceTexture(GetPieceTexture(PieceType, PieceColor));
}

UTexture2D* UChessComponent::GetPieceTexture(EPieceType PieceType, ETeam PieceColor)
{
	if (PieceType == EPieceType::EMPTY || PieceColor == ETeam::NONE)
	{
		UE_LOG(LogTemp, Error, TEXT("[UChessComponent::GetPieceTexture] Invalid Data."));
		return nullptr;
	}

	int Index = PieceType;
	if (PieceColor == ETeam::WHITE) Index += 6;

	if (Index - 1 > PiecesTexture.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("[UChessComponent::GetPieceTexture] Out of range."));
		return nullptr;
	}

	return PiecesTexture[Index - 1];
}


