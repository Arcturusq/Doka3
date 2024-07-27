//

#include "HookAbilityComponent.h"
#include "doka3Character.h" 
#include "HookProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h" 

UHookAbilityComponent::UHookAbilityComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityDamage = 300.0f;
	AbilityCastRange = 500.0f;
	AbilityRange = AbilityCastRange;
	AbilityManaCost = 100.0f;
	Cooldown = 10.0f;
	bIsReady = true; // ����������� ������ � ������������� ��� ������ ����

	AbilityType = EAbilityType::Channeled;

	//OwnerDoka3Character = Cast<Adoka3Character>(GetOwner());
}

void UHookAbilityComponent::ActivateAbility(Adoka3Character* OwnCharacter)
{
	Super::ActivateAbility(OwnCharacter);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Ability activated"));
	Super::CooldownExpired();
}

void UHookAbilityComponent::ActivateChannelingAbility(Adoka3Character* OwnCharacter)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ActivateChannelingAbility"));

	FVector TargetPosition = GetMousePosition(OwnCharacter);

	//  ��������,  ���  ������  �����  ��  ������
	if (TargetPosition != FVector::ZeroVector)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("TargetPosition != FVector::ZeroVector"));
		//  ��������  ������  ������  "Hook"
		UClass* HookClass = AHookProjectile::StaticClass();

		AHookProjectile* HookActor = GetWorld()->SpawnActor<AHookProjectile>(HookClass,
			OwnCharacter->GetActorLocation(), FRotator::ZeroRotator);
		HookActor->OwnerCharacter = OwnCharacter;


		if (HookActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("HookActor"));
			//  ����������  ���������  ��������  �  �����������
			HookActor->ProjectileMovement->Velocity = (TargetPosition - OwnCharacter->GetActorLocation()).GetSafeNormal() * fHookSpeed;

			//  ...  ������  ���������  ����  ...
		}
	}
}
