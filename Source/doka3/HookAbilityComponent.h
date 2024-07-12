//

#pragma once

#include "CoreMinimal.h"
#include "AbilityComponent.h"
#include "HookAbilityComponent.generated.h"

/**
 *
 */
UCLASS()
class DOKA3_API UHookAbilityComponent : public UAbilityComponent
{
	GENERATED_BODY()
public:
	UHookAbilityComponent(const FObjectInitializer& ObjectInitializer);

	virtual void ActivateAbility(ACharacter* OwnCharacter)override;

};
