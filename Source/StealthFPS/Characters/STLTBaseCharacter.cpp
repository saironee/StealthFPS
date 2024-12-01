// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/STLTBaseCharacter.h"

// Sets default values
ASTLTBaseCharacter::ASTLTBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsDead = false;

	GetMesh()->SetCollisionProfileName(TEXT("LivingEntity"));
	GetMesh()->SetCollisionObjectType(ECC_GameTraceChannel1);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ASTLTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

void ASTLTBaseCharacter::TakeAttack(EAttackType DamageType, AActor* DamageCauser, float Damage)
{
	if(Health <= 0)
		Die();
	else
		Health -= Damage;
	
	switch (DamageType)
	{
	case EAttackType::BULLET:
		BulletHit();
		break;;
	case EAttackType::TAKEDOWN:
		Takedown(DamageCauser);
		break;
	default:
		break;
	}
}

void ASTLTBaseCharacter::Die()
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bIsDead = true;
}

void ASTLTBaseCharacter::SetHealth(FString FName, float newHelath)
{
	if(GetName() == FName)
		Health = newHelath;
}
