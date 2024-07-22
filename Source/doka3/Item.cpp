
#include "Item.h"
#include "Battlefield.h"


void UItem::PlaceItem(UBattlefield* battlefield, FVector2D gridPosition)
{
    // Установка позиции ItemMesh в 3D-пространстве
    ItemMesh->SetWorldLocation(FVector(gridPosition.X, gridPosition.Y, 0));
    ItemMesh->SetVisibility(true);
}

void UItem::RemoveItemFromBattlefield()
{
    ItemMesh->SetVisibility(false);
}

void UItem::ActivateItem()
{
}
