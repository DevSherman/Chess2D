#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCamera.generated.h"

UCLASS()
class CHESS2D_API APlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	APlayerCamera();

protected:
	virtual void BeginPlay() override;

public:	
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere) class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere) class UChessComponent* ChessComponent;

private:
	class APlayerController* Controller;
};
