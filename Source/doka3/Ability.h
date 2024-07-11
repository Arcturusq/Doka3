// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Ability.generated.h"

/**
 *
 */
UCLASS(Abstract)
class DOKA3_API UAbility : public UObject
{
	GENERATED_BODY()

public:
	UAbility();
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityAttributes")
		float AbilityDamage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityAttributes")
		float AbilityCastRange = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityAttributes")
		float AbilityRange = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityAttributes")
		float AbilityManaCost = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityAttributes")
		float Cooldown = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityAttributes")
		bool bIsReady = true;


	UFUNCTION(BlueprintCallable, Category = "ActivateAbility")
		virtual void ActivateAbility(ACharacter* OwnCharacter);
protected:
	virtual void BeginPlay() override;
};
