// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h" 
class Adoka3Character;
class UHookAbilityComponent;
#include "HookProjectile.generated.h"

UCLASS()
class DOKA3_API AHookProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHookProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle ReturnTimerHandle; // Таймер
	float ReturnTimerInterval = 0.1f; // Интервал таймера (0.1 секунды)
	void OnReturnTimer();

	FTimerHandle DistanceTimerHandle; // Таймер
	float DistanceTimerInterval = 0.1f; // Интервал таймера (0.1 секунды)
	void OnDistanceTimer();

	bool ReturnRunned = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USphereComponent* CollisionComp;


	FVector StartLocation;

	AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OwnerCharacter")
	Adoka3Character* OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OwnerCharacter")
	UHookAbilityComponent* HookAbility;

	UFUNCTION(BlueprintCallable, Category = "ReturnHook")
	void ReturnHook();

	UFUNCTION(BlueprintCallable, Category = "PullTarget")
	void PullTarget();

	UFUNCTION(BlueprintCallable, Category = "Collision")
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "End")
	void HookEnd();
};
