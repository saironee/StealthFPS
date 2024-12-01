// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enums/EGunType.h"

#include "Enums/EMovementType.h"

#include "STLTPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHFPS_API USTLTPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	
public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;

//Variable
protected:
	TObjectPtr<class ASTLTPlayerCharacter> PlayerCharacter;
	TObjectPtr<class UCharacterMovementComponent> PlayerMovement;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMovementType MovementType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 bIsMove : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 bIsZoom : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 bIsFire : 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 bIsTakedown : 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 bIsChoke : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EGunType CurrentGunType;
};
