//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
class UStateWidget;
class UAbilityComponent;
#include "doka3Character.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEndEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

UCLASS(Blueprintable)
class Adoka3Character : public ACharacter
{
	GENERATED_BODY()

public:
	Adoka3Character();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float fRotationSpeed = 6.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float fHealth = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float fMaxHealth = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float fMana = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float fMaxMana = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float fDamage = 75.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float fAttackRange = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float fAttackSpeedRate = 2;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AttackTarget(ACharacter* Target);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HitTarget(ACharacter* Target);

	void RangeAttack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void MeleeAttack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void OnAnimAttackEnd(bool AttackSuccess);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void StopAttack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void DealDamage(Adoka3Character* DamageTarget);

	// Функция для применения урона
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, Adoka3Character* DamageCauser);

	// Переопределение функции получения урона
	void ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, Adoka3Character* DamageCauser);

	// Event to be broadcasted when attack occurs
	UPROPERTY(BlueprintAssignable, Category = "Attack")
	FOnAttackEvent OnAttack;

	UPROPERTY(BlueprintAssignable, Category = "Attack")
	FOnAttackEndEvent OnAttackEnd;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void AddAbility(UAbilityComponent* NewAbility);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void ActivateAbility(int32 AbilityIndex);

	// Функция для вызова события
	void ChangeHealth(float Delta);

	bool bIsAttacking = false;

	float fCharacterMaxSpeed = 600;

	// Ссылка на анимационный монтаж
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* AttackAnimMontage;

	ACharacter* TargetedEnemy;
	ACharacter* AttackEnemy;

	UStateWidget* CharacterWidget;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	UWidgetComponent* CharacterWidgetComponent;

	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<UAbilityComponent*> Abilities;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};

