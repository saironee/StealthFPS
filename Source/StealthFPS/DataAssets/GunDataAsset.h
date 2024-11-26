// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GunDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STEALTHFPS_API UGunDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMesh> BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	FTransform BodyTransform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	uint8 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	uint8 SubAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	uint8 SubMaxAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	uint8 CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float FireSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float ReloadSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> AimFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> RloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TSubclassOf<UAnimInstance> AnimBlueprint;
};
