
#include "Item.h"
#include "Battlefield.h"


UItem::UItem()
{
	ItemMesh->SetVisibility(false);
}

void UItem::PlaceItem(UBattlefield* battlefield, FVector2D gridPosition)
{
	// ��������� ������� ItemMesh � 3D-������������
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
