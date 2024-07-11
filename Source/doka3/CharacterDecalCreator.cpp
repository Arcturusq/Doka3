
#include "CharacterDecalCreator.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/DecalComponent.h"

UTexture* UCharacterDecalCreator::YourTextureObject = nullptr;


UMaterialInstanceDynamic* UCharacterDecalCreator::CreateDecalMaterialDynamic(UObject* Outer, UMaterialInterface* BaseMaterial)
{
	if (!BaseMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseMaterial is null"));
		return nullptr;
	}
	UMaterialInstanceDynamic* DecalMaterialDynamic = UMaterialInstanceDynamic::Create(BaseMaterial, Outer);
	if (!DecalMaterialDynamic)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create a dynamic material instance"));
		return nullptr;
	}
	// Здесь вы можете установить параметры материала, такие как цвет, прозрачность и текстуры
	// Например:
	DecalMaterialDynamic->SetVectorParameterValue(FName("Color"), FLinearColor::Red);
	DecalMaterialDynamic->SetScalarParameterValue(FName("Opacity"), 0.5f);

	if (YourTextureObject)
	{
		DecalMaterialDynamic->SetTextureParameterValue(FName("Texture"), YourTextureObject);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("YourTextureObject is null or invalid"));
	}
	return DecalMaterialDynamic;
}

void UCharacterDecalCreator::SetupDecalComponent(UDecalComponent* DecalComponent, UMaterialInterface* BaseMaterial)
{
	UObject* Outer = DecalComponent->GetOuter();
	UMaterialInstanceDynamic* DecalMaterialDynamic = CreateDecalMaterialDynamic(Outer, BaseMaterial);

	DecalComponent->SetDecalMaterial(DecalMaterialDynamic);
	DecalComponent->DecalSize = FVector(100.0f, 100.0f, 1.0f); // Размер декали
	// Другие настройки компонента
}

void UCharacterDecalCreator::SetupDecal(UMaterialInterface* BaseDecalMaterial, AActor* TargetActor)
{
	if (!BaseDecalMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseDecalMaterial is null"));
		return;
	}
	if (!TargetActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetActor is null"));
		return;
	}

	UDecalComponent* DecalComponent = NewObject<UDecalComponent>(TargetActor);
	if (DecalComponent)
	{
		DecalComponent->RegisterComponent();
		if (TargetActor->GetRootComponent())
		{
			DecalComponent->AttachToComponent(TargetActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		}
		SetupDecalComponent(DecalComponent, BaseDecalMaterial);
	}
}
