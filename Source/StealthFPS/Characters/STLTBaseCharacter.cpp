// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/STLTBaseCharacter.h"

// Sets default values
ASTLTBaseCharacter::ASTLTBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASTLTBaseCharacter::TakeAttack(EAttackType DamageType, AActor* DamageCauser, float Damage)
{
	if(Health <= 0)
	{
		Die();
	}
	Health -= Damage;
}

void ASTLTBaseCharacter::Die()
{
	Destroy();
}

void ASTLTBaseCharacter::SetHealth(FString FName, float newHelath)
{
	if(GetName() == FName)
		Health = newHelath;
}
