// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun/Gun.h"

#include "DataAssets/GunDataAsset.h"

#include <Components/StaticMeshComponent.h>

#include <InputMappingContext.h>
#include <InputAction.h>
#include <GameFramework/PlayerController.h>

#include "Characters/STLTPlayerCharacter.h"
#include <Components/SkeletalMeshComponent.h>
#include "Animation/AnimInstance.h"

#include "Camera/CameraComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting Gun
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = Body;

	//Set Iuput
	ConstructorHelpers::FObjectFinder<UInputMappingContext>
		IMCGunRef(TEXT("/Game/Input/IMC_Gun.IMC_Gun"));
	if(IMCGunRef.Succeeded())
		IMCGun = IMCGunRef.Object;

	ConstructorHelpers::FObjectFinder<UInputAction>
		IAFireRef(TEXT("/Game/Input/InputAction/IA_Fire.IA_Fire"));
	if(IAFireRef.Succeeded())
		IAFire = IAFireRef.Object;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	// Input Mapping Context 추가
	if (APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem && IMCGun)
		{
			Subsystem->AddMappingContext(IMCGun, 1);
		}
	}

	// 직접 호출
	SetupPlayerInputComponent();
}


// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::SetupPlayerInputComponent()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("총기결함 총기결함!"));
		return;
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	if(EnhancedInputComponent){
		EnhancedInputComponent->BindAction(IAFire, ETriggerEvent::Triggered, this, &AGun::Fire);
	}
}

void AGun::RefreshBody()
{
	if(Mother != nullptr)
		Body->SetStaticMesh(Mother->BodyMesh);
	Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if(FatherCharacter = Cast<ASTLTPlayerCharacter>(GetOwner()))
	{
		FatherCharacter->GetMesh()->SetAnimInstanceClass(Mother->AnimBlueprint);
	}
}

void AGun::FireEnd()
{
	bIsFire = false;
}

void AGun::Fire(const FInputActionValue& Value)
{
	if(Mother->CurrentAmmo <= 0 || bIsFire)
		return;
	
	bIsFire = true;
	Mother->CurrentAmmo--;

	UCameraComponent* PlayerCamera = FatherCharacter->GetCameraComponent();
}

void AGun::Reload()
{
	if(Mother->CurrentAmmo + Mother->SubAmmo <= Mother->MaxAmmo)
	{
		Mother->CurrentAmmo += Mother->SubAmmo;
		Mother->SubAmmo = 0;
	}else
		Mother->CurrentAmmo = Mother->MaxAmmo;
}
