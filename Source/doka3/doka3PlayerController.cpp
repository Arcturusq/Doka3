// Copyright Epic Games, Inc. All Rights Reserved.

#include "doka3PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "doka3Character.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"

Adoka3PlayerController::Adoka3PlayerController()
{
	bShowMouseCursor = true;

}

void Adoka3PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	MoveScreenByMouse();



	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}
void Adoka3PlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = Cast<Adoka3Character>(GetPawn());


	if (MyCharacter)
	{
		MyCharacter->GetCameraBoom()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
	//else
	//{
	//	// ��������� ������ ���������� ����
	//}
}
void Adoka3PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &Adoka3PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &Adoka3PlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Ability1", IE_Pressed, this, &Adoka3PlayerController::Use1Spell1);
	InputComponent->BindAction("Ability2", IE_Pressed, this, &Adoka3PlayerController::Use2Spell1);
	InputComponent->BindAction("Ability3", IE_Pressed, this, &Adoka3PlayerController::Use3Spell1);
	InputComponent->BindAction("Ability4", IE_Pressed, this, &Adoka3PlayerController::Use4Spell1);
	InputComponent->BindAction("Ability5", IE_Pressed, this, &Adoka3PlayerController::Use5Spell1);
	InputComponent->BindAction("Ultimate", IE_Pressed, this, &Adoka3PlayerController::Use6Spell1);

}

void Adoka3PlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void Adoka3PlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		// �������� ��������� � �������� ����� �����
		if (MyCharacter)
		{
			if (MyCharacter->TargetedCharacter && MyCharacter->TargetedCharacter != MyCharacter)
			{
				MyCharacter->AttackEnemy = MyCharacter->TargetedCharacter;
			}
			else
			{

				MyCharacter->StopAttack();
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
			}
		}
	}
}

void Adoka3PlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void Adoka3PlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void Adoka3PlayerController::MoveScreenByMouse()
{
	float mouseX, mouseY;
	int32 ViewportSizeX, ViewportSizeY;
	GetMousePosition(mouseX, mouseY);
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	float Xrat = mouseX / ViewportSizeX;
	float Yrat = mouseY / ViewportSizeY;

	CameraMoveSpeedX = (Xrat >= 0.9) ? 5.f : (Xrat <= 0.1 ? -5.f : 0.f);//������� ������ ���� ��� �����, �� ��� X
	if (Yrat >= 0.9)CameraMoveSpeedY = -5.f;
	else if (Yrat <= 0.1)CameraMoveSpeedY = 5.f;
	else CameraMoveSpeedY = 0.f;

	FVector DeltaLocation(CameraMoveSpeedY * MouseSensitivity, CameraMoveSpeedX * MouseSensitivity, 0.f);
	MyCharacter->GetCameraBoom()->AddWorldOffset(DeltaLocation);
}

void Adoka3PlayerController::Use1Spell1()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("q"));
	if (MyCharacter)
	{
		MyCharacter->ActivateAbility(0);
	}
}

void Adoka3PlayerController::Use2Spell1()
{
	if (MyCharacter)
	{
		MyCharacter->ActivateAbility(1);
	}
}

void Adoka3PlayerController::Use3Spell1()
{
	if (MyCharacter)
	{
		MyCharacter->ActivateAbility(2);
	}
}

void Adoka3PlayerController::Use4Spell1()
{
	if (MyCharacter)
	{
		MyCharacter->ActivateAbility(3);
	}
}

void Adoka3PlayerController::Use5Spell1()
{
	if (MyCharacter)
	{
		MyCharacter->ActivateAbility(4);
	}
}

void Adoka3PlayerController::Use6Spell1()
{
	if (MyCharacter)
	{
		MyCharacter->ActivateAbility(5);
	}
}


