// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();
	
protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float FireRange;

	FTimerHandle FireRateTimerHandle;
	float FireRate;

	void CheckFireCondition();

	bool CheckFireRange();

public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
};
