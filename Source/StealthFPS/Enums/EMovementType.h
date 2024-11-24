#pragma once

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	WALK 		UMETA(DisplayName = "Walk"),
	SIT			UMETA(DisplayName = "Sit"),
	FACEDOWN    UMETA(DisplayName = "Facedown"),
	RUN			UMETA(DisplayName = "Run"),
	JUMP		UMETA(DisplayName = "Jump"),
	DIE			UMETA(DisplayName = "Die"),
};