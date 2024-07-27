
#include "InventoryCell.h"
#include "Item.h"

void UInventoryCell::SetItem(UItem* item)
{
	if (ItemImage)
	{
		// Установите иконку предмета 
		ItemImage->SetBrushFromTexture(item->ItemIcon);
	}

	if (ItemNameText)
	{
		// Установите имя предмета 
		ItemNameText->SetText(FText::FromString(item->ItemName));
	}
}

void UInventoryCell::ClearItem()
{
	CurrentItem = nullptr;

	// Очистите UI
	if (ItemImage)
	{
		ItemImage->SetBrushFromTexture(nullptr);
	}
	if (ItemNameText)
	{
		ItemNameText->SetText(FText::FromString(""));
	}
}

void UInventoryCell::OnClicked()
{
}

void UInventoryCell::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent)
{
}

void UInventoryCell::OnDropDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent)
{
}
