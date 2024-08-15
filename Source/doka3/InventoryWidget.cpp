
#include "InventoryWidget.h"
#include "InventoryCell.h"
#include "Inventory.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*for (int32 i = 0; i < 6; i++) {
		InventoryCells.Add(CreateWidget<UInventoryCell>(GetWorld(), UInventoryCell::StaticClass()));
	}

	for (UInventoryCell* CellWidget : InventoryCells)
	{
		if (CellWidget)
		{
			CellWidget->AddToViewport();
		}
	}*/

	// »нициализируйте массив InventoryCells
	//InitializeInventoryCells();

	// ...
}

//void UInventoryWidget::InitializeInventoryCells()
//{
//	InventoryCells.SetNum(6);
//	// ”бедитесь, что количество €чеек в массиве соответствует
//	// количеству €чеек, добавленных в UVerticalBox в редакторе.
//	if (InventoryCells.Num() != 6)
//	{
//		// ќшибка:  оличество €чеек не совпадает!
//		return;
//	}
//
//	// Ќастройка свойств €чеек
//	for (int32 i = 0; i < InventoryCells.Num(); i++)
//	{
//		InventoryCells[i] = CreateWidget<UInventoryCell>(GetWorld(), UInventoryCell::StaticClass());
//		InventoryCells[i]->SlotIndex = i;
//		InventoryCells[i]->AddToRoot();
//		// ... ƒополнительна€ настройка €чеек
//	}
//
//	// ќбновите UI €чеек
//	UpdateInventoryUI();
//}

//void UInventoryWidget::UpdateInventoryUI()
//{
//	// ѕройдите по всем €чейкам инвентар€
//	for (int32 i = 0; i < InventoryCells.Num(); i++)
//	{
//		UInventoryCell* Cell = InventoryCells[i];
//		UItem* Item = PlayerInventory->GetItemAtSlot(Cell->SlotIndex); // ѕолучите предмет из UInventory
//
//		// ќбновление €чейки
//		if (Item)
//		{
//			Cell->SetItem(Item);
//		}
//		else
//		{
//			Cell->ClearItem();
//		}
//	}
//}

void UInventoryWidget::OnItemDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent)
{
}

void UInventoryWidget::OnItemDropDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent)
{
}

void UInventoryWidget::OnItemClicked(UItem* Item)
{
}

void UInventoryWidget::OnItemActivated(UItem* Item)
{
}
