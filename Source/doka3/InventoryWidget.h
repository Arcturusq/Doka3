// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ListView.h"
class UItem;
class UInventory;
class UInventoryCell;
#include "InventoryWidget.generated.h"

/**
 *
 */
UCLASS()
class DOKA3_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TArray<UInventoryCell*> InventoryCells;

	// ‘ункции дл€ обновлени€ UI
	void UpdateInventoryUI();
	void OnItemDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);
	void OnItemDropDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);
	void OnItemClicked(UItem* Item);
	void OnItemActivated(UItem* Item);

protected:

	// —сылки на UI-элементы
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TArray<UImage*> ItemImageWidgets;
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	UListView* AvailableItemsList;

	// —сылка на инвентарь
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	UInventory* PlayerInventory;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeInventoryCells();

	void NativeConstruct();
};
