// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
class UItem;
#include "InventoryCell.generated.h"

/**
 *
 */
UCLASS()
class DOKA3_API UInventoryCell : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryCell")
	int32 SlotIndex;
	UPROPERTY(EditDefaultsOnly, Category = "InventoryCell")
	UImage* ItemImage;
	UPROPERTY(EditDefaultsOnly, Category = "InventoryCell")
	UTextBlock* ItemNameText;
	UPROPERTY(meta = (BindWidget))
	UButton* ItemButton;
	UPROPERTY(BlueprintReadWrite, Category = "InventoryCell")
	UItem* CurrentItem;

	void SetItem(UItem* item);
	void ClearItem();

	// Функции для обработки событий
	void OnButtonClicked();
	void OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);
	void OnDropDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);

protected:
	virtual void NativeConstruct() override;
};
