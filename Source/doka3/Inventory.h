// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
class UItem;
#include "Inventory.generated.h"

/**
 *
 */
UCLASS()
class DOKA3_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<UItem*> Items;

	UFUNCTION(BlueprintCallable, Category = "ActionsWithItem")
	UItem* GetItemAtSlot(int32 slotIndex);

	UFUNCTION(BlueprintCallable, Category = "ActionsWithItem")
	bool HasItem(UItem* item);

	UFUNCTION(BlueprintCallable, Category = "ActionsWithItem")
	bool AddItem(UItem* item);

	UFUNCTION(BlueprintCallable, Category = "ActionsWithItem")
	bool RemoveItem(UItem* item);

	UFUNCTION(BlueprintCallable, Category = "ActionsWithItem")
	void SwapItems(int32 slotIndex1, int32 slotIndex2);


	UFUNCTION(BlueprintCallable, Category = "UIActions")
	void UpdateUI();

	UFUNCTION(BlueprintCallable, Category = "UIActions")
	void HandleItemDrag(UItem* item, FVector2D gridPosition);

	UFUNCTION(BlueprintCallable, Category = "UIActions")
	void HandleItemDrop(UItem* item, FVector2D gridPosition);

	UFUNCTION(BlueprintCallable, Category = "UIActions")
	void HandleItemActivation(UItem* item);
};
