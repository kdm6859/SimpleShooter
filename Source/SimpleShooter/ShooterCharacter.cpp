// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem != nullptr)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	////PlayerInputComponent->BindAction(TEXT("LookUp"), this, AShooterCharacter::LookUp);
	//PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	//PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	//PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);

	//PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);



	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (Input != nullptr)
	{
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterCharacter::NewMove);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterCharacter::NewLook);
	}
}

//void AShooterCharacter::MoveForward(float AxisValue)
//{
//	AddMovementInput(GetActorForwardVector(), AxisValue);
//}
//
//void AShooterCharacter::MoveRight(float AxisValue)
//{
//	AddMovementInput(GetActorRightVector(), AxisValue);
//} 
//
//void AShooterCharacter::LookUpRate(float AxisValue)
//{
//	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
//}
//
//void AShooterCharacter::LookRightRate(float AxisValue)
//{
//	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
//}


void AShooterCharacter::NewMove(const FInputActionInstance& Instance)
{
	FVector2D MovementVector = Instance.GetValue().Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(FowardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		UE_LOG(LogTemp, Warning, TEXT("XXXXX : %f, YYYYY : %f"), MovementVector.X, MovementVector.Y);
	}
}

void AShooterCharacter::NewLook(const FInputActionInstance& Instance)
{
	FVector2D LookVector = Instance.GetValue().Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}



