// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Hook.generated.h"

/**
 * 
 */
UCLASS()
class DOKA3_API UHook : public UAbility
{
	GENERATED_BODY()

public:
	UHook();
	virtual void ActivateAbility(ACharacter* OwnCharacter) override;
	float speed;

protected:
	virtual void Tick(float DeltaSeconds) override;
};
