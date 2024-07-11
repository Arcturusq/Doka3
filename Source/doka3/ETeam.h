// Team.h
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
    TEAM_None UMETA(DisplayName = "None"),
    TEAM_Red UMETA(DisplayName = "Red Team"),
    TEAM_Blue UMETA(DisplayName = "Blue Team"),
    // Добавьте другие команды по необходимости
};