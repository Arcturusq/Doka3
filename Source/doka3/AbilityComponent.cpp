// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"

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

void UAbilityComponent::ActivateAbility(ACharacter* OwnCharacter)
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
        StartChanneling(OwnCharacter);
        break;
    }
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UAbilityComponent::CooldownExpired, Cooldown, false);
}

void UAbilityComponent::ActivateTargetedAbility(ACharacter* OwnCharacter)
{
}

void UAbilityComponent::ActivateSelfAbility(ACharacter* OwnCharacter)
{
}

void UAbilityComponent::ActivateAOEAbility(ACharacter* OwnCharacter)
{
}

void UAbilityComponent::StartChanneling(ACharacter* OwnCharacter)
{
}

void UAbilityComponent::CooldownExpired()
{
	bIsReady = true;
	UE_LOG(LogTemp, Warning, TEXT("Ability is ready again!"));
}
