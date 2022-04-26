// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

#include "Kismet/GameplayStatics.h"

#include "GameFramework/DamageType.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

#include "Camera/CameraShakeBase.h"

// Sets default values
AProjectile::AProjectile()
	: BaseMesh(nullptr), ProjectileMovement(nullptr), HitParticles(nullptr), Damage(100.f)
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->InitialSpeed = 1500.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particles"));
	TrailParticles->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	/*UE_LOG
	(
		LogTemp, Warning,
		TEXT("Component %s have hit Actor %s and Component %s"),
		*HitComp->GetName(),
		*OtherActor->GetName(),
		*OtherComp->GetName()
	);*/
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}

	AController* OnwerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, OnwerInstigator, this, DamageTypeClass);
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation
			(
				this,
				HitParticles,
				GetActorLocation(),
				GetActorRotation()
			);
			
			if (HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
			}

			if (HitCameraShakeClass)
			{
				GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
			}
		}
	}

	Destroy();
}

