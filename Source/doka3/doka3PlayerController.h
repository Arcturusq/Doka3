// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
class Adoka3Character;
#include "doka3PlayerController.generated.h"

UCLASS()
class Adoka3PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	Adoka3PlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface


	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	Adoka3Character* MyCharacter;

	void MoveScreenByMouse();

	float CameraMoveSpeedX = 0.f;
	float CameraMoveSpeedY = 0.f;

	float MouseSensitivity = 3.f;



	void Use1Spell1();
	void Use2Spell1();
	void Use3Spell1();
	void Use4Spell1();
	void Use5Spell1();
	void Use6Spell1();
protected:
	virtual void BeginPlay() override;
};


