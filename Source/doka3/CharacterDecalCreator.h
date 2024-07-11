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
	// ������� ��� �������� ������������� ��������� ������
	static UMaterialInstanceDynamic* CreateDecalMaterialDynamic(UObject* Outer, UMaterialInterface* BaseMaterial);

	// ������� ��� ��������� ���������� ������
	static void SetupDecalComponent(UDecalComponent* DecalComponent, UMaterialInterface* BaseMaterial);

	// ������� ��� ������������� ������
	void SetupDecal(UMaterialInterface* BaseDecalMaterial, AActor* TargetActor);

	// ���������� ��������� �� ��������
	static UTexture* YourTextureObject;
};
