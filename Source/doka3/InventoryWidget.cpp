
#include "InventoryWidget.h"
#include "InventoryCell.h"
#include "Inventory.h"


void UInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // ��������������� ������ InventoryCells
    InitializeInventoryCells();

    // ...
}

void UInventoryWidget::InitializeInventoryCells()
{
    // ���������, ��� ���������� ����� � ������� �������������
    // ���������� �����, ����������� � UVerticalBox � ���������.
    if (InventoryCells.Num() != 6)
    {
        // ������: ���������� ����� �� ���������!
        return;
    }

    // ��������� ������� �����
    for (int32 i = 0; i < InventoryCells.Num(); ++i)
    {
        InventoryCells[i]->SlotIndex = i;
        // ... �������������� ��������� �����
    }

    // �������� UI �����
    UpdateInventoryUI();
}

void UInventoryWidget::UpdateInventoryUI()
{
    // �������� �� ���� ������� ���������
    for (int32 i = 0; i < InventoryCells.Num(); ++i)
    {
        UInventoryCell* Cell = InventoryCells[i];
        UItem* Item = PlayerInventory->GetItemAtSlot(Cell->SlotIndex); // �������� ������� �� UInventory

        // ���������� ������
        if (Item)
        {
            Cell->SetItem(Item);
        }
        else
        {
            Cell->ClearItem();
        }
    }
}

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
