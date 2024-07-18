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

	virtual void ActivateAbility(Adoka3Character* OwnCharacter)override;

	virtual void ActivateChannelingAbility(Adoka3Character* OwnCharacter)override;

};
