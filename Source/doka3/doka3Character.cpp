//

#include "doka3Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "StateWidget.h"
#include "Engine/World.h"
#include "AbilityComponent.h"
#include "HookAbilityComponent.h"


Adoka3Character::Adoka3Character()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Создание компонента виджета и прикрепление его к корневому компоненту
	CharacterWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CharacterWidget"));
	CharacterWidgetComponent->SetupAttachment(RootComponent);

	// Установка класса виджета
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("WidgetBlueprint'/Game/Widgets/StateWidget.StateWidget_C'"));
	if (WidgetClass.Succeeded())
	{
		CharacterWidgetComponent->SetWidgetClass(WidgetClass.Class);
	}

	// Настройка положения виджета
	CharacterWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f)); // Примерное положение над головой персонажа
	CharacterWidgetComponent->SetDrawSize(FVector2D(100.0f, 100.0f)); // Размер виджета

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Загрузка анимационного монтажа
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontageObject(TEXT("AnimMontage'/Game/Animations/SwordAttack_Montage.SwordAttack_Montage'"));
	if (AnimMontageObject.Succeeded())
	{
		AttackAnimMontage = AnimMontageObject.Object;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Succeeded"));
	}

	Abilities.SetNum(6);
	for (int i = 0; i <= 5; i++)
	{
		Abilities[i] = nullptr;
	}
	UHookAbilityComponent* HookAbility = CreateDefaultSubobject<UHookAbilityComponent>(TEXT("HookAbility"));
	AddAbility(HookAbility, 0); // Добавление способности в массив
}

void Adoka3Character::BeginPlay()
{
	Super::BeginPlay();

	this->GetCharacterMovement()->MaxWalkSpeed = fCharacterMaxSpeed;

	CharacterWidget = Cast<UStateWidget>(CharacterWidgetComponent->GetUserWidgetObject());
	CharacterWidget->SetOwner(this);

}

void Adoka3Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Это просто ПИЗДЕЦ. Такого быть не должно. перенести в controller сделать обработку отмены атаки
	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Pawn, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);

			// Новый код для определения цели
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit Actor: %s"), *GetNameSafe(TraceHitResult.GetActor())));
			ACharacter* HitCharacter = Cast<ACharacter>(TraceHitResult.GetActor());
			if (HitCharacter) // Проверяем, что персонаж не пытается атаковать сам себя
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("hit"));
				TargetedCharacter = HitCharacter;
			}
			else
			{
				TargetedCharacter = nullptr;
			}

		}
	}
	if (AttackEnemy)
	{
		AttackTarget(AttackEnemy);
	}
}

void Adoka3Character::AttackTarget(ACharacter* Target)
{
	if (Target)
	{

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("attack"));
		float DistanceSquared = FVector::DistSquared(GetActorLocation(), Target->GetActorLocation());
		if (DistanceSquared <= FMath::Square(fAttackRange))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("asd"));

			// Вычисляем направление к цели
			FVector DirectionToTarget = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			// Создаем новый ротатор, который смотрит в направлении цели
			FRotator TargetRotation = DirectionToTarget.Rotation();

			// Получаем текущий ротатор персонажа
			FRotator CurrentRotation = GetActorRotation();

			// Сохраняем текущее значение вращения по оси Z
			float CurrentPitch = CurrentRotation.Pitch;
			float CurrentRoll = CurrentRotation.Roll;

			// Создаем новый ротатор с текущими значениями по оси X и Y, но с новым значением по оси Z
			FRotator NewTargetRotation = FRotator(CurrentPitch, TargetRotation.Yaw, CurrentRoll);

			// Интерполируем к новому ротатору
			FRotator NewRotation = FMath::RInterpTo(CurrentRotation, NewTargetRotation, GetWorld()->GetDeltaSeconds(), fRotationSpeed);

			// Применяем новый ротатор к персонажу
			SetActorRotation(NewRotation);


			DirectionToTarget.Z = 0; // Убираем компонент Z
			DirectionToTarget.Normalize();
			// Получаем вектор вперед актора и устанавливаем его Z в 0
			FVector ForwardVector = GetActorForwardVector();
			ForwardVector.Z = 0; // Убираем компонент Z
			ForwardVector.Normalize(); // Нормализуем вектор

			// Проверяем, достаточно ли персонаж повернулся для атаки
			if (FVector::DotProduct(DirectionToTarget, ForwardVector) > 0.99f) // 0.99f - это косинус угла близкого к 0 градусов
			{
				MeleeAttack();
			}
			// Здесь должен быть код, который наносит урон или выполняет другие действия атаки
		}
		else // Если цель слишком далеко, подходим к ней
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PPC"));
			// Получаем контроллер и вызываем функцию движения к точке
			AController* MyController = GetController();
			if (MyController)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("GAGAGA"));
				UAIBlueprintHelperLibrary::SimpleMoveToActor(MyController, Target);
			}
		}
		/*if (Target && (FVector::Dist(GetActorLocation(), Target->GetActorLocation()) <= AttackRange)) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("asd"));
		}*/
	}
}

void Adoka3Character::RangeAttack()
{
}

void Adoka3Character::HitTarget(ACharacter* Target)
{

}

void Adoka3Character::MeleeAttack()
{
	OnAttack.Broadcast();
	if (bIsAttacking == false)
	{
		bIsAttacking = true;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("MaxWalkSpeed = 0"));
		this->GetCharacterMovement()->StopMovementImmediately();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("playAnim"));
		PlayAnimMontage(AttackAnimMontage, fAttackSpeedRate);
	}
}

void Adoka3Character::OnAnimAttackEnd(bool AttackSuccess = true)
{

	Adoka3Character* DamageTarget = Cast<Adoka3Character>(AttackEnemy);
	OnAttackEnd.Broadcast();
	bIsAttacking = false;
	this->GetCharacterMovement()->MaxWalkSpeed = fCharacterMaxSpeed;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("OnAnimAttackEnd"));
	if (AttackSuccess)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("AttackSuccess"));
		DealDamage(fDamage, DamageTarget);
	}

}

void Adoka3Character::StopAttack()
{
	OnEnemyDead.Broadcast();
	StopAnimMontage(AttackAnimMontage);
	AttackEnemy = nullptr;
	OnAnimAttackEnd(false);
}

void Adoka3Character::AddAbility(UAbilityComponent* NewAbility, int32 Index)
{
	if (NewAbility && Index >= 0 && Index < Abilities.Num())
	{
		Abilities[Index] = NewAbility;
	}
}

void Adoka3Character::ActivateAbility(int32 AbilityIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("w"));
	if (Abilities.IsValidIndex(AbilityIndex) && Abilities[AbilityIndex])
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("e"));
		Abilities[AbilityIndex]->ActivateAbility(this);
	}
}

void Adoka3Character::ChangeHealth(float Delta)
{
	this->fHealth += Delta;
	OnHealthChanged.Broadcast();
	CharacterWidget->UpdateProgressBar();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ChangeHealth"));
}

// Функция для применения урона
void Adoka3Character::ApplyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, Adoka3Character* DamageCauser)
{
	if (!this) return;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("ApplyDamage"));
	this->ChangeHealth(-Damage);
	// Проверка на смерть
	if (this->fHealth <= 0.0f)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DEATH"));
		// Логика смерти или уничтожения актора
		if (!DamageCauser) return;
		DamageCauser->StopAttack();
		this->Destroy();
	}
}

void Adoka3Character::DealDamage(float Damage, Adoka3Character* DamageTarget)
{
	DamageTarget->ApplyDamage(Damage, nullptr, Cast<APlayerController>(GetController()), this);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("DealDamage"));
}

void Adoka3Character::ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, Adoka3Character* DamageCauser)
{
	ApplyDamage(Damage, DamageType, InstigatedBy, DamageCauser);
}