// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
class UBattlefield;
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

	// ������ ��������
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	UTexture2D* ItemIcon;

	// ������� �������� ��������
	UFUNCTION(BlueprintCallable, Category = "BattleFieldActions")
	void PlaceItem(UBattlefield* battlefield, FVector2D gridPosition);

	// ������� �������� �������� � ���� �����-
	UFUNCTION(BlueprintCallable, Category = "BattleFieldActions")
	void RemoveItemFromBattlefield();

	UFUNCTION(BlueprintCallable, Category = "ActivateItem")
	void ActivateItem();


};
