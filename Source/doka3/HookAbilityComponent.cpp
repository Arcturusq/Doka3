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
	bIsReady = true; // Способность готова к использованию при начале игры
}

void UHookAbilityComponent::ActivateAbility(ACharacter* OwnCharacter)
{
	Super::CooldownExpired();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ability activated"));
	Super::CooldownExpired();
}
