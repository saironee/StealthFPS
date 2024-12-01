// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/STLTPlayerAnimInstance.h"

#include "Characters/STLTPlayerCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>

#include "Gun/Gun.h"

void USTLTPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(PlayerCharacter = Cast<ASTLTPlayerCharacter>(GetOwningActor()))
	{
		PlayerMovement = PlayerCharacter->GetCharacterMovement();
	}
}

void USTLTPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if(PlayerCharacter){
		MovementType = PlayerCharacter->GetMovementType();

		FVector Velocity = PlayerCharacter->GetVelocity();
		if(Velocity.Size2D() > 0)
			bIsMove = true;
		else
			bIsMove = false;

		bIsZoom = PlayerCharacter->bCanAim;
		bIsTakedown = PlayerCharacter->bIsTakedwon;
		bIsChoke = PlayerCharacter->bIsChoke;
		CurrentGunType = PlayerCharacter->CurrentGunType;
	}
}
