// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "STLTInventoryDataAsset.generated.h"

/**
 * 
 */
UCLASS(BLueprintable)
class STEALTHFPS_API USTLTInventoryDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = Ammo)
	int32 SubAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 SubMaxAmmo;
};
