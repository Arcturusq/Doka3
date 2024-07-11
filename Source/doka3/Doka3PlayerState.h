// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ETeam.h"
#include "Doka3PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DOKA3_API ADoka3PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    // Свойство для хранения команды игрока
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team")
        ETeam PlayerTeam;
};