// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"



UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	//void MoveForward(float AxisValue);
	//void MoveRight(float AxisValue);
	//void LookUpRate(float AxisValue);
	//void LookRightRate(float AxisValue);

	UPROPERTY(EditAnywhere)
	float RotationRate = 20;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	UPROPERTY()
	AGun* Gun;


	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ShootAction;


protected:
	void NewMove(const struct FInputActionInstance& Instance);
	void NewLook(const FInputActionInstance& Instance);
	void Shoot();

};
