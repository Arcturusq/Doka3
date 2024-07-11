#include "doka3Character.h"

#include "StateWidget.h"

UStateWidget::UStateWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // ������������� ���������� � ��������� �������
}

void UStateWidget::UpdateProgressBar()
{
	if (!doka3CharacterOwner.IsValid()) {
		return;
	}
	HealthBar->SetPercent(doka3CharacterOwner->fHealth / doka3CharacterOwner->fMaxHealth);
}
