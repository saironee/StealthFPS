// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UFUNCTION(Blueprintable)
	void SetBrother(class USTLTInventoryDataAsset* newBro) { Brother = newBro; };
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mother)
	TObjectPtr<class UGunDataAsset> Mother;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mother)
	TObjectPtr<class USTLTInventoryDataAsset> Brother;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mother)
	TObjectPtr<class ASTLTPlayerCharacter> FatherCharacter;

//Reload
protected:
	virtual void Reload() override;
	virtual void EndReload() override;


//Fire
protected:	
	virtual void FireEnd() override;
	void FireRay();

protected:
	UPROPERTY(VIsibleAnywhere, BlueprintReadOnly, Category = Fire)
	int32 CurrentAmmo;

//Input	
public:
	void OnFire();
	void OnReload();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	uint8 bIsFire : 1 = false;

//Reload
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	uint8 bCanReload : 1 = true;
};
