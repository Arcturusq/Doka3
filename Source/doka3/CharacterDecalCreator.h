// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/DecalComponent.h"
#include "CharacterDecalCreator.generated.h"

/**
 *
 */
UCLASS()
class DOKA3_API UCharacterDecalCreator : public UObject
{
	GENERATED_BODY()

public:
	// Функция для создания динамического материала декали
	static UMaterialInstanceDynamic* CreateDecalMaterialDynamic(UObject* Outer, UMaterialInterface* BaseMaterial);

	// Функция для настройки компонента декали
	static void SetupDecalComponent(UDecalComponent* DecalComponent, UMaterialInterface* BaseMaterial);

	// Функция для инициализации декали
	void SetupDecal(UMaterialInterface* BaseDecalMaterial, AActor* TargetActor);

	// Объявление указателя на текстуру
	static UTexture* YourTextureObject;
};
