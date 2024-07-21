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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float fHookSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OwnerCharacter")
	Adoka3Character* OwnerDoka3Character;

	virtual void ActivateAbility(Adoka3Character* OwnCharacter)override;

	virtual void ActivateChannelingAbility(Adoka3Character* OwnCharacter)override;

};
