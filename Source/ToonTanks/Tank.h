// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

	bool bAlive;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate;

	UPROPERTY(Category = "Components", VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(Category = "Components", VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY()
	APlayerController* PlayerController;

	void Move(float Value);
	void Turn(float Value);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const;
};
