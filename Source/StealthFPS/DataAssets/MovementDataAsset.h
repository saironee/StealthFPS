// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MovementDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHFPS_API UMovementDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = Stat)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float CameraDistance = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float CameraHeight = 50.f;
};
