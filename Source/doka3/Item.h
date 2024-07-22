// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
class UBattlefield;
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class DOKA3_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	UStaticMeshComponent* ItemMesh;
	
	// Функция выкладки предмета
	UFUNCTION(BlueprintCallable, Category = "BattleFieldActions")
	void PlaceItem(UBattlefield* battlefield, FVector2D gridPosition);

	// Функция удаления предмета с поля битвы-
	UFUNCTION(BlueprintCallable, Category = "BattleFieldActions")
	void RemoveItemFromBattlefield();

	UFUNCTION(BlueprintCallable, Category = "ActivateItem")
	void ActivateItem();
};
