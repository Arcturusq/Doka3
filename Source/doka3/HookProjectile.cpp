// Fill out your copyright notice in the Description page of Project Settings.

#include "HookProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h" 
#include "Components/SphereComponent.h"
#include "doka3Character.h"
#include "HookAbilityComponent.h"

// Sets default values
AHookProjectile::AHookProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(StaticMeshComponent);
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
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

}

// Called when the game starts or when spawned
void AHookProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHookProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AHookProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OwnerCharacter: %s"), OwnerCharacter ? *OwnerCharacter->GetName() : TEXT("nullptr")));
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		if (OtherActor != OwnerCharacter) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OtherActor != OwnerCharacter"));
			TargetActor = OtherActor;
			PullTarget();
		}
	}
}

void AHookProjectile::PullTarget()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("PullTarget"));

}