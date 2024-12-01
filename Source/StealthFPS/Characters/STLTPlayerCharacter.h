// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/STLTBaseCharacter.h"

#include "InputActionValue.h"

#include "Enums/EMovementType.h"
#include "Gun/Gun.h"

#include "STLTPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHFPS_API ASTLTPlayerCharacter : public ASTLTBaseCharacter
{
	GENERATED_BODY()

public:
	ASTLTPlayerCharacter();

public:	
	virtual void BeginPlay() override;
	
protected:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

//Camera Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;


//Scene Setcion
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Takedown)
	TObjectPtr<USceneComponent> TakedownScene;
	
//Input Section
protected:
	void Movement(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OnAim(const FInputActionValue& Value);
	void ReleaseAim(const FInputActionValue& Value);
	void OnRun(const FInputActionValue& Value);
	void ReleaseRun(const FInputActionValue& Value);
	void Sit(const FInputActionValue& Value);
	void OnFire(const FInputActionValue& Value) { if(MyGun || !bIsTakedwon){ MyGun->OnFire(); } }
	void OnReload(const FInputActionValue& Value){ if(MyGun || !bIsTakedwon){  MyGun->OnReload(); } }
	void OnTakeDown(const FInputActionValue& Value);
	void ReleaseTakeDown(const FInputActionValue& Value);
	
	void InitializeMovementMap();
	void SetCamera(float DeltaTime);
	void SetRun();

protected:
	uint8 bCanRun : 1;
	
public:	
	void SetMovementType(EMovementType Type);
	
	UFUNCTION(BlueprintPure)
	EMovementType GetMovementType() { return CurrentMovementType; }
	
	uint8 bCanAim : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Child")
	TObjectPtr<class AGun> MyGun;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	class UCameraComponent* GetCameraComponent() { return Camera; };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Takedwon")
	uint8 bIsTakedwon : 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Takedwon")
	uint8 bIsChoke : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Takedwon")
	EGunType CurrentGunType;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> IMCDefault;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IAMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IALook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IAAim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IARun;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputAction> IASit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IAFire;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IAReload;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IATakedown;

protected:
	TMap<EMovementType, TObjectPtr<class UMovementDataAsset>> MovementMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zoom")
	float ZoomSpeed = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zoom")
	float SitDownSpeed = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Takedown")
	float TakedownLength = 100.f;
	
	float CameraTargetOffset;
	float CameraTargetHeightOffset;
	EMovementType CurrentMovementType;
};
