// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"


UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	Targeted,
	Self,
	AOE,
	Passive,
	Channeled
};

UCLASS(Abstract, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DOKA3_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilityComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Объект для управления таймером восстановления
	FTimerHandle CooldownTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityAttributes")
	float AbilityDamage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityAttributes")
	float AbilityCastRange = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityAttributes")
	float AbilityRange = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityAttributes")
	float AbilityManaCost = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	float Cooldown = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	bool bIsReady = true;

	UPROPERTY(EditDefaultsOnly, Category = "AbilityType")
	EAbilityType AbilityType;


	UFUNCTION(BlueprintCallable, Category = "ActivateAbility")
	virtual void ActivateAbility(ACharacter* OwnCharacter);

	UFUNCTION(BlueprintCallable, Category = "ActivateAbility")
	virtual void ActivateTargetedAbility(ACharacter* OwnCharacter);

	UFUNCTION(BlueprintCallable, Category = "ActivateAbility")
	virtual void ActivateSelfAbility(ACharacter* OwnCharacter);

	UFUNCTION(BlueprintCallable, Category = "ActivateAbility")
	virtual void ActivateAOEAbility(ACharacter* OwnCharacter);

	UFUNCTION(BlueprintCallable, Category = "ActivateAbility")
	virtual void StartChanneling(ACharacter* OwnCharacter);
	
	

	// Функция для обработки таймера восстановления
	UFUNCTION(BlueprintCallable, Category = "CooldownAbility")
	virtual void CooldownExpired();

};
