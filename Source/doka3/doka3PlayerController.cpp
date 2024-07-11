// Copyright Epic Games, Inc. All Rights Reserved.

#include "doka3PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "doka3Character.h"
#include "Engine/World.h"

Adoka3PlayerController::Adoka3PlayerController()
{
	bShowMouseCursor = true;
}

void Adoka3PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void Adoka3PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &Adoka3PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &Adoka3PlayerController::OnSetDestinationReleased);

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
		/*float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{*/

		//}
		// Получаем персонажа и вызываем метод атаки
		Adoka3Character* MyCharacter = Cast<Adoka3Character>(GetPawn());
		if (MyCharacter) {
			if (MyCharacter->TargetedEnemy) {
				//MyCharacter->AttackTarget(MyCharacter->TargetedEnemy);
				MyCharacter->AttackEnemy = MyCharacter->TargetedEnemy;
			}
			else {
				MyCharacter->AttackEnemy = nullptr;
				if (MyCharacter->bIsAttacking) {
					MyCharacter->StopAttack();
				}
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
