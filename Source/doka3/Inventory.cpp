// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

UItem* UInventory::GetItemAtSlot(int32 slotIndex)
{
	return nullptr;
}

bool UInventory::HasItem(UItem* item)
{
	return false;
}

bool UInventory::AddItem(UItem* item)
{
	return false;
}

bool UInventory::RemoveItem(UItem* item)
{
	return false;
}

void UInventory::SwapItems(int32 slotIndex1, int32 slotIndex2)
{
}

void UInventory::UpdateUI()
{
}

void UInventory::HandleItemDrag(UItem* item, FVector2D gridPosition)
{
}

void UInventory::HandleItemDrop(UItem* item, FVector2D gridPosition)
{
}

void UInventory::HandleItemActivation(UItem* item)
{
}
