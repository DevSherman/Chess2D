#include "ChessComponent.h"
#include "Core/ChessEngine.h"
#include "UI/ChessBoardUI.h"
#include "UI/CBoxUI.h"
#include "Core/ChessTypes.h"
#include "Utls.h"
#include "Core/Utls.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

UChessComponent::UChessComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Engine = NewObject<UChessEngine>();
	Bot = NewObject<UChessBot>();
	Bot->Init(*Engine, 0, ETeam::BLACK);
}

void UChessComponent::CreateBoard()
{
	PiecesTexture = Utls::LoadAssetsFromPath<UTexture2D>("/Game/Textures/Pieces/");
	SoundEffects = Utls::LoadAssetsFromPath<USoundBase>("/Game/Sounds/Effects/");

	W_ChessBoardUI = Utls::LoadBlueprintFromPath<UChessBoardUI>("'/Game/Widgets/W_ChessBoardUI.W_ChessBoardUI'");
	UI = CreateWidget<UChessBoardUI>(GetWorld(), W_ChessBoardUI);
	if (!UI) { UE_LOG(LogTemp, Error, TEXT("[UChessComponent: %s] UI not initilizaed.")); return; }

	UI->AddToViewport();
	UI->Init(*this);

	UE_LOG(LogTemp, Warning, TEXT("[UChessComponent] Board Created."));

	LoadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	UE_LOG(LogTemp, Warning, TEXT("[UChessComponent] Pieces placed."));

	PlaySoundEffect(0); //start game
}

void UChessComponent::LoadFEN(FString FEN)
{
	//"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"
	//"rnbqkbnr/8/8/8/8/8/8/RNBQKBNR"
	int row = 7;
	int column = 0;

	for (int i = 0; i < FEN.Len(); i++)
	{
		char c = FEN[i];

		if (isalpha(c))
		{
			SpawnPiece(c, column, row);
			column++;
		}
		else if (isalnum(c))
		{
			column += (int)c - 1;
			if(column == 7) row--;
		}
		else //-> '/'
		{
			row--;
			column = 0;
		}
	}
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

void UChessComponent::UpdateCBoxUI(int X, int Y, EPieceType Piece, ETeam Team)
{
	CBoxUIArray[X][Y]->SetPieceTexture(GetPieceTexture(Piece, Team));
}

void UChessComponent::ClearCBoxUI(int X, int Y)
{
	CBoxUIArray[X][Y]->Clear();
	//UE_LOG(LogTemp, Warning, TEXT("[UChessComponent::ClearCBoxUI] : [%s] Cleared"), *ChessUtls::GetCoordName(FCoord{ X, Y }));
}

void UChessComponent::ShowInfoPositions(TArray<FMovement> MovesArray)
{
	for (int i = 0; i < ValidMovements.Movements.Num(); i++)
		CBoxUIArray[ValidMovements.Movements[i].Coord.X][ValidMovements.Movements[i].Coord.Y]->SetFrameInfo(GetInfo(ValidMovements.Movements[i].Type));	
}
void UChessComponent::ClearInfoPositions()
{
	for (int i = 0; i < ValidMovements.Movements.Num(); i++)
		CBoxUIArray[ValidMovements.Movements[i].Coord.X][ValidMovements.Movements[i].Coord.Y]->SetFrameInfo(EInfoType::CLEAR_TYPE);
	ValidMovements.Movements.Empty();
}

void UChessComponent::OnClickPressed()
{
	if (!CurrentCBoxUI || PlayerTeam != CurrentTeam) return;

	MoveToCursor();
}

void UChessComponent::MoveToCursor()
{
	CurrentData = Engine->GetData(CurrentCBoxUI->GetCoord());
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("CurrentData: [%s]"), *ChessUtls::GetCoordName(CurrentData->Coord)));

	ValidMovements = Engine->GetMovementsFromData(*CurrentData);
	if (ValidMovements.Movements.Num() == 0) return;

	Engine->ClearBoard(CurrentCBoxUI->GetCoord());
	UTexture2D* texture = GetPieceTexture(CurrentData->PieceType, CurrentData->Team);
	if (texture) UI->SetCursorImage(texture);
	else UE_DEBUG_BREAK();
	
	ShowInfoPositions(ValidMovements.Movements);
	CurrentCBoxUI->Clear();
}

void UChessComponent::OnClickReleased()
{
	if (ValidMovements.Movements.Num() == 0) return;

	if (CurrentData) //mouse slot data
	{
		if (CurrentCBoxUI) //move
		{
			int Index = Engine->IsValidMovement(CurrentCBoxUI->GetCoord());
			if (Index > -1)
			{
				FMovement move = ValidMovements.Movements[Index];
				ValidMovements.FinalMoveIndex = Index;

				if (move.Type == EMovementType::L_CASTLING || move.Type == EMovementType::S_CASTLING) Castling(move.Coord);

				CurrentCBoxUI->SetPieceTexture(UI->GetImageFromCursor());
				CurrentData->Coord = CurrentCBoxUI->GetCoord();
				Engine->UpdateBoard(CurrentData);

				UE_LOG(LogTemp, Warning, TEXT("%s"), *Engine->GetNotation(ValidMovements));

				SoundEffect(move.Type);

				NextTeamTurn();
				OpenentMove();
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
}

ETeam UChessComponent::GetOpenentTeam() const
{
	if (PlayerTeam == ETeam::WHITE) return ETeam::BLACK;
	if (PlayerTeam == ETeam::BLACK) return ETeam::WHITE;
	return ETeam::NONE;
}

void UChessComponent::OpenentMove()
{
	FMovementResultArray result = Bot->GetRandomMove();
	//if (result.CurrentCoord.X < 0 || result.CurrentCoord.Y < 0) UE_DEBUG_BREAK();
	if (result.bIsValid)
	{
		FMovement move = result.Movements[result.FinalMoveIndex];
		UpdateCBoxUI(move.Coord.X, move.Coord.Y, result.Piece, result.Team);
		ClearCBoxUI(result.CurrentCoord.X, result.CurrentCoord.Y);
		CBoxUIArray[move.Coord.X][move.Coord.Y]->SetFrameInfo(GetInfo(move.Type));

		UE_LOG(LogTemp, Warning, TEXT("%s"), *Engine->GetNotation(result));

		NextTeamTurn();
	}
	else OpenentMove();
}

void UChessComponent::ResetPos()
{
	CBoxUIArray[CurrentData->Coord.X][CurrentData->Coord.Y]->SetPieceTexture(UI->GetImageFromCursor());
	Engine->UpdateBoard(CurrentData, true);
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

EInfoType UChessComponent::GetInfo(EMovementType Type)
{
	EInfoType infoType{};
	if (Type == EMovementType::CAPTURE || Type == EMovementType::PASSANT)
		infoType = EInfoType::CAPTURE_TYPE;
	if (Type == EMovementType::MOVE || Type == EMovementType::S_CASTLING || Type == EMovementType::L_CASTLING)
		infoType = EInfoType::MOVE_TYPE;

	return infoType;
}

void UChessComponent::SoundEffect(EMovementType Type)
{
	//TOOD: Check move type
	switch (Type)
	{
		case EMovementType::MOVE:
		{
			if (CurrentData->Team == WHITE) PlaySoundEffect(1);
			if (CurrentData->Team == BLACK) PlaySoundEffect(2);
			break;
		}
		case EMovementType::CAPTURE:
		{
			if (CurrentData->Team == WHITE) PlaySoundEffect(5);
			if (CurrentData->Team == BLACK) PlaySoundEffect(6);
			break;
		}
		case EMovementType::S_CASTLING: case EMovementType::L_CASTLING:
		{
			if (CurrentData->Team == WHITE) PlaySoundEffect(3);
			if (CurrentData->Team == BLACK) PlaySoundEffect(4);

			break;
		}
	}
}

void UChessComponent::PlaySoundEffect(int Index)
{
	UGameplayStatics::PlaySound2D(GetWorld(), SoundEffects[Index]);
}

void UChessComponent::SpawnPiece(EPieceType PieceType, ETeam PieceColor, int X, int Y)
{
	Engine->UpdateBoard(new ChessBoxData(PieceType, PieceColor, X, Y), true);
	CBoxUIArray[X][Y]->SetPieceTexture(GetPieceTexture(PieceType, PieceColor));
}

void UChessComponent::SpawnPiece(char c, int X, int Y)
{
	ETeam Team = isupper(c) ? ETeam::WHITE : ETeam::BLACK;
	EPieceType Piece = EPieceType::EMPTY;

	switch (c)
	{
		case 'r': case 'R': Piece = EPieceType::ROOK; break;
		case 'n': case 'N': Piece = EPieceType::KNIGHT; break;
		case 'b': case 'B': Piece = EPieceType::BISHOP; break;
		case 'q': case 'Q': Piece = EPieceType::QUEEN; break;
		case 'k': case 'K': Piece = EPieceType::KING; break;
		case 'p': case 'P': Piece = EPieceType::PAWN; break;
	}
	SpawnPiece(Piece, Team, X, Y);
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


