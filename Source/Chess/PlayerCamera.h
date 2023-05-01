#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCamera.generated.h"

UCLASS()
class CHESS_API APlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	APlayerCamera();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	class UCameraComponent* Camera;

private:
	void LeftClickDown();
	void LeftClickUp(); 

	class UMainController* MainController;
};
