// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "doka3Character.h"
#include "doka3PlayerController.h"


UAbilityComponent::UAbilityComponent(const FObjectInitializer& ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbilityComponent::ActivateAbility(Adoka3Character* OwnCharacter)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("UAbilityComponent::ActivateAbility"));
	switch (AbilityType)
	{
	case EAbilityType::Targeted:
		ActivateTargetedAbility(OwnCharacter);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Targeted"));
		break;
	case EAbilityType::Self:
		ActivateSelfAbility(OwnCharacter);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Self"));
		break;
	case EAbilityType::AOE:
		ActivateAOEAbility(OwnCharacter);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("AOE"));
		break;
	case EAbilityType::Passive:
		// Activate passively, or simply do nothing here.
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Passive"));
		break;
	case EAbilityType::Channeled:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Channeled:"));
		ActivateChannelingAbility(OwnCharacter);
		break;
	default:
		break;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("switch canseled"));
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UAbilityComponent::CooldownExpired, Cooldown, false);
}

void UAbilityComponent::ActivateTargetedAbility(Adoka3Character* OwnCharacter)
{
}

void UAbilityComponent::ActivateSelfAbility(Adoka3Character* OwnCharacter)
{
}

void UAbilityComponent::ActivateAOEAbility(Adoka3Character* OwnCharacter)
{
}

void UAbilityComponent::ActivateChannelingAbility(Adoka3Character* OwnCharacter)
{
	Adoka3PlayerController* PlayerController = Cast<Adoka3PlayerController>(OwnCharacter->GetController());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("UAbilityComponent::ActivateChannelingAbility"));

	if (PlayerController)
	{
		// Получите позицию курсора в мире
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, true, HitResult);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("if (PlayerController)"));
		// Проверьте, что курсор попал на объект
		if (HitResult.bBlockingHit)
		{
			// Используйте позицию курсора
			FVector MousePosition = HitResult.Location;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, TEXT("if (HitResult.bBlockingHit)"));

			UClass* CharacterClass = Adoka3Character::StaticClass();
			Adoka3Character* NewCharacter = GetWorld()->SpawnActor<Adoka3Character>(CharacterClass, MousePosition, FRotator::ZeroRotator);
			

			// ... ваш код, использующий MousePosition ...

			// Например, вы можете показать эффект на этой позиции:
			// SpawnEffectAtLocation(MousePosition);

			// Или вызвать функцию в персонаже, передав позицию:
			// OwnCharacter->DoSomethingWithMousePosition(MousePosition);
		}
	}
}

void UAbilityComponent::CooldownExpired()
{
	bIsReady = true;
	UE_LOG(LogTemp, Warning, TEXT("Ability is ready again!"));
}
