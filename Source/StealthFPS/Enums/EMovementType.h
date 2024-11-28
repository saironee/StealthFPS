#pragma once

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	WALK 		UMETA(DisplayName = "Walk"),
	SIT			UMETA(DisplayName = "Sit"),
	RUN			UMETA(DisplayName = "Run"),
};