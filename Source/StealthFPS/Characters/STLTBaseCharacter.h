// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Enums/EAttackType.h"
#include "Interface/ISTLTTakeAttack.h"

#include "STLTBaseCharacter.generated.h"

UCLASS()
class STEALTHFPS_API ASTLTBaseCharacter : public ACharacter, public IISTLTTakeAttack
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTLTBaseCharacter();

public:
	virtual void BeginPlay() override;
	
//Dead or Alive And TakeAttack
protected:
	UFUNCTION(BlueprintCallable)
	virtual void TakeAttack(EAttackType DamageType, AActor* DamageCauser, float Damage) override;


/*
 *BulletHit,
 *Takedown 과 같은 맞았을 때 반응 구현은 자식이 직접하도록!
 */
	UFUNCTION(BlueprintCallable)
	void BulletHit() {}
	
	UFUNCTION(BlueprintCallable)
	virtual void Takedown(AActor* DamageCauser) {}
	
	UFUNCTION(BLueprintCallable, Category = "Health")
	virtual void Die();
		
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly = "Die")
	uint8 bIsDead : 1;
	
//Cheat
protected:
	UFUNCTION(Exec)
	void SetHealth(FString Name, float newHelath);
};
