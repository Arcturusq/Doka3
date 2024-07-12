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