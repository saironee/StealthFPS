// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "STLTSoldierAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHFPS_API USTLTSoldierAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	TObjectPtr<class ASTLTEmemyCharacter> EnemyCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	uint8 bIsDead : 1;
};
