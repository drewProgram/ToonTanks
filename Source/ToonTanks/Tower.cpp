// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"

#include "Tank.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


ATower::ATower()
	: Tank(nullptr), FireRange(500.f), FireRate(3.f)
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::CheckFireCondition()
{
	if (!Tank)
	{
		return;
	}

	if (CheckFireRange() && Tank->bAlive)
	{
		Fire();
	}
}

bool ATower::CheckFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}

		return false;
	}

	UE_LOG(LogTemp, Error, TEXT("Tank is null pointer"));

	return false;
}


void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
