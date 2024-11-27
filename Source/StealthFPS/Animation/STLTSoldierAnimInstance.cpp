// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/STLTSoldierAnimInstance.h"
#include "Characters/STLTEmemyCharacter.h"

void USTLTSoldierAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	EnemyCharacter = Cast<ASTLTEmemyCharacter>(GetOwningActor());
}

void USTLTSoldierAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(EnemyCharacter)
	{
		bIsDead = EnemyCharacter->bIsDead;
	}
}
