// Fill out your copyright notice in the Description page of Project Settings.

#include "HookProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h" 
#include "Components/SphereComponent.h"
#include "doka3Character.h"
#include "HookAbilityComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AHookProjectile::AHookProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(StaticMeshComponent);
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	// Создаем сферу для коллизий
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(10.0f);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AHookProjectile::OnOverlapBegin);
	CollisionComp->SetupAttachment(RootComponent); // Подключаем к корневому компоненту

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);


		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
	OwnerCharacter = nullptr;



}

// Called when the game starts or when spawned
void AHookProjectile::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();

	GetWorldTimerManager().SetTimer(DistanceTimerHandle, this, &AHookProjectile::OnReturnTimer, DistanceTimerInterval, true);

}

void AHookProjectile::OnReturnTimer()
{
	if (OwnerCharacter)
	{
		// Вычисляем расстояние до OwnerCharacter
		float DistanceToOwner = FVector::Dist(GetActorLocation(), OwnerCharacter->GetActorLocation());

		// Если расстояние больше 50, двигаемся к OwnerCharacter
		if (DistanceToOwner > 50.0f)
		{
			FVector Direction = (OwnerCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			ProjectileMovement->Velocity = Direction * ProjectileMovement->MaxSpeed;
		}

		// Иначе, останавливаемся 
	}
}

void AHookProjectile::OnDistanceTimer()
{
	if (HookAbility) {
		// Проверяем расстояние между текущим положением и стартовой точкой
		float DistanceFromStart = FVector::Dist(GetActorLocation(), StartLocation);

		// Если расстояние превышает определённое значение, вызываем ReturnHook
		if (DistanceFromStart > 1000000.0f && !ReturnRunned)
		{
			ReturnHook();
		}
	}
}

// Called every frame
void AHookProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AHookProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OwnerCharacter: %s"), OwnerCharacter ? *OwnerCharacter->GetName() : TEXT("nullptr")));
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		if (OtherActor != OwnerCharacter && OwnerCharacter) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OtherActor != OwnerCharacter"));
			TargetActor = OtherActor;
			PullTarget();
		}
		else if (TargetActor && OtherActor == OwnerCharacter && OwnerCharacter) {
			HookEnd();
		}
	}
}

void AHookProjectile::HookEnd()
{

	GetWorldTimerManager().ClearTimer(ReturnTimerHandle);
	if (TargetActor) {

		//TargetActor->SetActorEnableCollision(true);

		TArray<UPrimitiveComponent*> Components;
		TargetActor->GetComponents(Components);
		for (auto Component : Components)
		{
			Component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}

		FVector TargetLocation = TargetActor->GetActorLocation();

		// Привязываем TargetActor к AHookProjectile
		TargetActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		// Восстанавливаем положение TargetActor
		TargetActor->SetActorLocation(TargetLocation);


		// Получите текущий поворот актора
		FRotator CurrentRotation = TargetActor->GetActorRotation();

		// Измените угол поворота по горизонтали (например, на 90 градусов)
		CurrentRotation.Yaw = 90.f;

		// Установите новый поворот актора
		TargetActor->SetActorRotation(CurrentRotation);


		TargetActor = nullptr; // Сбрасываем указатель на объект
	}
	Destroy();
}

void AHookProjectile::ReturnHook()
{
	/*static bool alreadyCalled = true;
	if (alreadyCalled) return;
	alreadyCalled = true;*/

	if (ReturnRunned)return;
	ReturnRunned = true;
	GetWorldTimerManager().SetTimer(ReturnTimerHandle, this, &AHookProjectile::OnReturnTimer, ReturnTimerInterval, true);
}

void AHookProjectile::PullTarget()
{
	// Отключаем движение TargetActor
	//if (ACharacter* TargetedCharacter = Cast<ACharacter>(TargetActor))
	//{
	//	TargetedCharacter->GetCharacterMovement()->Velocity = FVector::ZeroVector;
	//	TargetedCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);
	//}


	if (TargetActor) {

		//TargetActor->SetActorEnableCollision(false);
		TArray<UPrimitiveComponent*> Components;
		TargetActor->GetComponents(Components);
		for (auto Component : Components)
		{
			Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		/* IfTargetedActorAttachedToSoething: (but Engine crashing :( )
		if (TargetActor->GetAttachParentActor()) {
			FVector DetachTargetLocation = TargetActor->GetActorLocation();

			// Привязываем TargetActor к AHookProjectile
			TargetActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			// Восстанавливаем положение TargetActor
			TargetActor->SetActorLocation(DetachTargetLocation);
		}*/

		FVector TargetLocation = TargetActor->GetActorLocation();

		// Привязываем TargetActor к AHookProjectile
		TargetActor->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

		// Восстанавливаем положение TargetActor
		TargetActor->SetActorLocation(TargetLocation);
	}



	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("PullTarget"));
	ReturnHook();
}