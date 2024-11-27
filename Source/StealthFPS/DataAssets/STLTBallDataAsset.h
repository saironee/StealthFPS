// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "STLTBallDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class STEALTHFPS_API USTLTBallDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 MinAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 MaxAmmo;
};
