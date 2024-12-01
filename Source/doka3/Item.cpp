
#include "Item.h"
#include "Battlefield.h"
#include "AbilityComponent.h"


UItem::UItem()
{
	//ItemMesh->SetVisibility(false);
}

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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Using Item"));
	if (!Ability) return;

	if (!OwnerCharacter) return;
	Ability->ActivateAbility(OwnerCharacter);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Using Ability of Item"));

}
