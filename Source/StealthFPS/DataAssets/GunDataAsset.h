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
	uint8 CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TSubclassOf<class UAnimInstance> AnimBlueprint;
};
