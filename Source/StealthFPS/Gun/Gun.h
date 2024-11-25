// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <InputActionValue.h>

#include "Interface/IReloadInterface.h"

#include "Gun.generated.h"

UCLASS()
class STEALTHFPS_API AGun : public AActor, public IIReloadInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetupPlayerInputComponent();

//Body
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Body)
	TObjectPtr<class UStaticMeshComponent> Body;

	UFUNCTION(BlueprintCallable)
	void RefreshBody();
//Mother
protected:
	UFUNCTION(Blueprintable)
	void SetMother(class UGunDataAsset* newMom) { Mother = newMom;};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mother)
	TObjectPtr<class UGunDataAsset> Mother;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mother)
	TObjectPtr<class ASTLTPlayerCharacter> FatherCharacter;

//Input
protected:
	void Fire(const FInputActionValue& Value);
	virtual void Reload() override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> IMCGun;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IAFire;

//Animation
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<class UAnimInstance> PlayerAnimInstanse;
};
