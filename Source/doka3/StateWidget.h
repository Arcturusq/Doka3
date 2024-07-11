// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "doka3Character.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "StateWidget.generated.h"

/**
 *
 */
UCLASS(Abstract)
class DOKA3_API UStateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UStateWidget(const FObjectInitializer& ObjectInitializer);
	void SetOwner(Adoka3Character* owner) { doka3CharacterOwner = owner; }
	void UpdateProgressBar();

protected:
	//virtual void NativeConstruct() override;
	TWeakObjectPtr<Adoka3Character> doka3CharacterOwner;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentHealthLabel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxHealthLabel;

};
