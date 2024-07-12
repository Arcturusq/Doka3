#include "StateWidget.h"
#include "doka3Character.h"


UStateWidget::UStateWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // Инициализация переменных и состояний виджета
}

void UStateWidget::UpdateProgressBar()
{
	if (!doka3CharacterOwner.IsValid()) {
		return;
	}
	HealthBar->SetPercent(doka3CharacterOwner->fHealth / doka3CharacterOwner->fMaxHealth);
}
