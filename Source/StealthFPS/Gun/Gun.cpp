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
	
	ConstructorHelpers::FObjectFinder<UInputAction>
		IAReloadRef(TEXT("/Game/Input/InputAction/IA_Reload.IA_Reload"));
	if(IAReloadRef.Succeeded())
		IAReload = IAReloadRef.Object;
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
		EnhancedInputComponent->BindAction(IAReload, ETriggerEvent::Triggered, this, &AGun::OnReload);
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

	Mother->CurrentAmmo = Mother->MaxAmmo;
}

void AGun::FireEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Finish Fire!"));
	bIsFire = false;
}

void AGun::Fire(const FInputActionValue& Value)
{
	if(Mother->CurrentAmmo <= 0)
		return;

	if(!bIsFire)
	{
		bIsFire = true;
		FireStartPosition = 0.f;
		
		Mother->CurrentAmmo--;

		if(UAnimInstance* AnimInstance = Cast<UAnimInstance>(FatherCharacter->GetMesh()->GetAnimInstance()))
		{
			if(FatherCharacter->bCanAim)
				AnimInstance->Montage_Play(Mother->AimFireMontage, Mother->FireSpeed);
			else
				AnimInstance->Montage_Play(Mother->FireMontage, Mother->FireSpeed);
		}
	}
}

void AGun::OnReload(const FInputActionValue& Value)
{
	if(Mother->CurrentAmmo >= Mother->MaxAmmo)
		return;
		
	if(bCanReload)
	{
		bCanReload = false;
		if(UAnimInstance* AnimInstance = Cast<UAnimInstance>(FatherCharacter->GetMesh()->GetAnimInstance()))
		{
			AnimInstance->Montage_Play(Mother->RloadMontage, Mother->ReloadSpeed);
		}
	}
}

void AGun::Reload()
{
	if (Mother->CurrentAmmo >= Mother->MaxAmmo || Mother->SubAmmo <= 0)
	{
		if(FatherCharacter = Cast<ASTLTPlayerCharacter>(GetOwner()))
		{
			FatherCharacter->GetMesh()->GetAnimInstance()->StopAllMontages(0.1f);
		}
		return;
	}
	
	uint8 AmmoNeeded = Mother->MaxAmmo - Mother->CurrentAmmo;
	
	uint8 AmmoToReload = FMath::Min(AmmoNeeded, Mother->SubAmmo);

	// 탄약 갱신
	Mother->CurrentAmmo += AmmoToReload;
	Mother->SubAmmo -= AmmoToReload;
}


void AGun::EndReload()
{
	bCanReload = true;
}
