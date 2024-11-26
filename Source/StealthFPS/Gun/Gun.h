// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <InputActionValue.h>

#include "Interface/IReloadInterface.h"
#include "Interface/STLTFireEndInterface.h"
#include "Interface/STLTEndReloadInterface.h"

#include "Gun.generated.h"

UCLASS()
class STEALTHFPS_API AGun : public AActor,
public IIReloadInterface,
public ISTLTFireEndInterface,
public ISTLTEndReloadInterface
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
	virtual void FireEnd() override;
	void Fire(const FInputActionValue& Value);
	void OnReload(const FInputActionValue& Value);
	virtual void Reload() override;
	virtual void EndReload() override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> IMCGun;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IAFire;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IAReload;

//Fire
protected:	
	FTimerHandle FireSpeedHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire")
	float FireStartPosition = 0.f;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	uint8 bIsFire : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	uint8 bIsReload : 1;

//Reload
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	uint8 bCanReload : 1 = true;
};
