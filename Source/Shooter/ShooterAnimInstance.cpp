// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}
	
	if (ShooterCharacter)
	{
		// Get the speed of the character from velocity
		FVector Velocity{ShooterCharacter->GetVelocity()};
		Velocity.Z = 0;
		Speed = Velocity.Size();

		// Is the Character in the air?
		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		// Is the character accelerating?
		if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		FRotator AnimRotation = ShooterCharacter->GetBaseAimRotation();
		FRotator MovementRotation =
			UKismetMathLibrary::MakeRotFromX(
				ShooterCharacter->GetVelocity());
		MovementOffset = UKismetMathLibrary::NormalizedDeltaRotator(
			MovementRotation,
			AnimRotation).Yaw;
		
		/*FString RotationMessage = FString::Printf(
			TEXT("Base Aim Rotation: %f"),
			AnimRotation.Yaw);*/
		
		/*FString MovementRotationMessage =
			FString::Printf(
				TEXT("Movement Rotation: %f"),
				MovementRotation.Yaw);*/
		
		/*FString OffsetMessage =
			FString::Printf(
			TEXT("Movement Offset Yaw: %f"),
			AnimRotation.Yaw);*/
		
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, OffsetMessage);
		}*/
	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	
}
