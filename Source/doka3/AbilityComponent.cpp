// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "doka3Character.h"
#include "doka3PlayerController.h"


UAbilityComponent::UAbilityComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) // Вызов конструктора базового класса
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
    switch (AbilityType)
    {
    case EAbilityType::Targeted:
        ActivateTargetedAbility(OwnCharacter);
        break;
    case EAbilityType::Self:
        ActivateSelfAbility(OwnCharacter);
        break;
    case EAbilityType::AOE:
        ActivateAOEAbility(OwnCharacter);
        break;
    case EAbilityType::Passive:
        // Activate passively, or simply do nothing here.
        break;
    case EAbilityType::Channeled:
        ActivateChannelingAbility(OwnCharacter);
        break;
    }
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
    if (PlayerController)
    {
        // Получите позицию курсора в мире
        FHitResult HitResult;
        PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, true, HitResult);

        // Проверьте, что курсор попал на объект
        if (HitResult.bBlockingHit)
        {
            // Используйте позицию курсора
            FVector MousePosition = HitResult.Location;


           


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
