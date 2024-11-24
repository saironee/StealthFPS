#pragma once

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	DAMAGE			UMETA(DisplayName = "Damage"),
	BULLET 			UMETA(DisplayName = "Bullet"),
	KNOCKBACK 		UMETA(DisplayName = "Knockback"),
	STUN			UMETA(DisplayName = "Stun"),
	ONEKILL			UMETA(DisplayName = "OneKill"),
};