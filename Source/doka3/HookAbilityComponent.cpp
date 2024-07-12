//

#include "HookAbilityComponent.h"

UHookAbilityComponent::UHookAbilityComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityDamage = 300.0f;
	AbilityCastRange = 500.0f;
	AbilityRange = AbilityCastRange;
	AbilityManaCost = 100.0f;
	Cooldown = 10.0f;
	bIsReady = true; // ����������� ������ � ������������� ��� ������ ����
}

void UHookAbilityComponent::ActivateAbility(ACharacter* OwnCharacter)
{
	if (bIsReady) {

	}
}
