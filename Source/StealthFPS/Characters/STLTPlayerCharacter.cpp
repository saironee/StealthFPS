// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/STLTPlayerCharacter.h"

#include <Components/SkeletalMeshComponent.h>

#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

#include <InputMappingContext.h>
#include <InputAction.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

#include "DataAssets/MovementDataAsset.h"
#include <GameFramework/CharacterMovementComponent.h>

#include <Components/SkeletalMeshComponent.h>

ASTLTPlayerCharacter::ASTLTPlayerCharacter() :
MyGun(nullptr)
{
	//Set Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	Camera->bUsePawnControlRotation = true;
	
	//Set Body
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		BodyRef(TEXT("/Game/Arms/PlayerArm/PlayerArm.PlayerArm"));
	if(BodyRef.Succeeded())
		GetMesh()->SetSkeletalMesh(BodyRef.Object);

	GetMesh()->SetupAttachment(Camera);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Set Input
	ConstructorHelpers::FObjectFinder<UInputMappingContext>
		IMCDefaultRef(TEXT("/Game/Input/IMC_Default.IMC_Default"));
	if(IMCDefaultRef.Succeeded())
		IMCDefault = IMCDefaultRef.Object;
	
	ConstructorHelpers::FObjectFinder<UInputAction>
		IAMovementRef(TEXT("/Game/Input/InputAction/IA_Movement.IA_Movement"));
	if(IAMovementRef.Succeeded())
		IAMovement = IAMovementRef.Object;

	ConstructorHelpers::FObjectFinder<UInputAction>
		IALookRef(TEXT("/Game/Input/InputAction/IA_Look.IA_Look"));
	if(IALookRef.Succeeded())
		IALook = IALookRef.Object;
	
	ConstructorHelpers::FObjectFinder<UInputAction>
		IAAimRef(TEXT("/Game/Input/InputAction/IA_Aim.IA_Aim"));
	if(IAAimRef.Succeeded())
		IAAim = IAAimRef.Object;

	ConstructorHelpers::FObjectFinder<UInputAction>
		IARunRef(TEXT("/Game/Input/InputAction/IA_Run.IA_Run"));
	if(IARunRef.Succeeded())
		IARun = IARunRef.Object;
	
	ConstructorHelpers::FObjectFinder<UInputAction>
		IASitRef(TEXT("/Game/Input/InputAction/IA_Sit.IA_Sit"));
	if(IASitRef.Succeeded())
		IASit = IASitRef.Object;

	InitializeMovementMap();
}

void ASTLTPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetMovementType(EMovementType::WALK);
	
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if(Subsystem)
		{
			Subsystem->AddMappingContext(IMCDefault, 0);
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("Add Mapping 안됨 ㅅㅂ"))
		}
	}else
		UE_LOG(LogTemp, Warning, TEXT("APlyerController Cast 안됨 ㅅㅂ"))
}

void ASTLTPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetCamera(DeltaTime);
	SetRun();
}

void ASTLTPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IAMovement, ETriggerEvent::Triggered, this, &ASTLTPlayerCharacter::Movement);
		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Triggered, this, &ASTLTPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(IAAim, ETriggerEvent::Triggered, this, &ASTLTPlayerCharacter::OnAim);
		EnhancedInputComponent->BindAction(IAAim, ETriggerEvent::Completed, this, &ASTLTPlayerCharacter::ReleaseAim);
		EnhancedInputComponent->BindAction(IARun, ETriggerEvent::Triggered, this, &ASTLTPlayerCharacter::OnRun);
		EnhancedInputComponent->BindAction(IARun, ETriggerEvent::Completed, this, &ASTLTPlayerCharacter::ReleaseRun);
		EnhancedInputComponent->BindAction(IASit, ETriggerEvent::Started, this, &ASTLTPlayerCharacter::Sit);
	}
}

void ASTLTPlayerCharacter::Movement(const FInputActionValue& Value)
{
	FVector2D MovementVactor = Value.Get<FVector2D>();
	
	AddMovementInput(GetActorForwardVector(), MovementVactor.X);
	AddMovementInput(GetActorRightVector(), MovementVactor.Y);
}

void ASTLTPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVactor = Value.Get<FVector2D>();

	AddControllerYawInput(LookVactor.X);
	AddControllerPitchInput(LookVactor.Y);
}

void ASTLTPlayerCharacter::OnAim(const FInputActionValue& Value)
{
	bCanAim = true;
	CameraTargetOffset = 50.f;
}

void ASTLTPlayerCharacter::ReleaseAim(const FInputActionValue& Value)
{
	bCanAim = false;
	SetMovementType(GetMovementType());
}

void ASTLTPlayerCharacter::OnRun(const FInputActionValue& Value)
{
	if(bCanRun)
	{
		bCanAim = false;
		SetMovementType(EMovementType::RUN);
	}
}

void ASTLTPlayerCharacter::ReleaseRun(const FInputActionValue& Value)
{
	SetMovementType(EMovementType::WALK);
}

void ASTLTPlayerCharacter::Sit(const FInputActionValue& Value)
{
	if(GetMovementType() == EMovementType::SIT)
		SetMovementType(EMovementType::WALK);
	else
		SetMovementType(EMovementType::SIT);
}

void ASTLTPlayerCharacter::InitializeMovementMap()
{
	MovementMap.Empty();
	
	for (int32 i = 0; i < static_cast<int32>(EMovementType::DIE) + 1; ++i)
	{
		EMovementType MovementType = static_cast<EMovementType>(i);
		
		FString EnumName = UEnum::GetValueAsString(MovementType);
		EnumName = EnumName.Replace(TEXT("EMovementType::"), TEXT("")); //EMovementType:: <- 접두사 제거
		
		FString Path = FString::Printf(TEXT("/Game/DataAssets/Movement/%s.%s"), *EnumName, *EnumName);
		
		UMovementDataAsset* DataAsset = ConstructorHelpers::FObjectFinder<UMovementDataAsset>(*Path).Object;

		if (DataAsset)
		{
			MovementMap.Add(MovementType, DataAsset);
			UE_LOG(LogTemp, Warning, TEXT("Sucsses"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed : %s"), *EnumName);
		}
	}
}

void ASTLTPlayerCharacter::SetMovementType(EMovementType Type)
{
	CurrentMovementType = Type;

	GetCharacterMovement()->MaxWalkSpeed = MovementMap[Type]->MovementSpeed;
	CameraTargetOffset = MovementMap[Type]->CameraDistance;
	CameraTargetHeightOffset = MovementMap[Type]->CameraHeight;
}


void ASTLTPlayerCharacter::SetCamera(float DeltaTime)
{
	float CurrentFOV = Camera->FieldOfView;
	float NewFOV = FMath::FInterpTo(CurrentFOV, CameraTargetOffset, DeltaTime, ZoomSpeed);
	Camera->SetFieldOfView(NewFOV);

	float CurrentHeight = Camera->GetRelativeLocation().Z;
	float NewHeight = FMath::FInterpTo(CurrentHeight, CameraTargetHeightOffset, DeltaTime, SitDownSpeed);
	Camera->SetRelativeLocation(
			FVector(Camera->GetRelativeLocation().X,
				Camera->GetRelativeLocation().Y,
				NewHeight));
}

void ASTLTPlayerCharacter::SetRun()
{
	bCanRun = GetVelocity().Size2D() > 0.f;
    if (!bCanRun)
    {
        SetMovementType(EMovementType::WALK);
    }
}
