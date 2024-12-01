// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
class UBattlefield;
class UAbilityComponent;
class Adoka3Character;
#include "Item.generated.h"

/**
 *
 */
UCLASS(Abstract)
class DOKA3_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();


	UPROPERTY(EditDefaultsOnly, Category = "Item")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FString ItemName;

	// Иконка предмета
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	UTexture2D* ItemIcon;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Item")
	Adoka3Character* OwnerCharacter;


	// Функция выкладки предмета
	UFUNCTION(BlueprintCallable, Category = "BattleFieldActions")
	void PlaceItem(UBattlefield* battlefield, FVector2D gridPosition);

	// Функция удаления предмета с поля битвы-
	UFUNCTION(BlueprintCallable, Category = "BattleFieldActions")
	void RemoveItemFromBattlefield();

	UFUNCTION(BlueprintCallable, Category = "ActivateItem")
	void ActivateItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	UAbilityComponent* Ability;


};
