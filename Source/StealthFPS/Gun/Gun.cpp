// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun/Gun.h"
#include "DataAssets/GunDataAsset.h"
#include <Components/StaticMeshComponent.h>
#include <GameFramework/PlayerController.h>
#include "Characters/STLTPlayerCharacter.h"
#include <Components/SkeletalMeshComponent.h>
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "DataAssets/STLTInventoryDataAsset.h"
#include "Mecro/STLTLivingEntity.h"
#include "Interface/ISTLTTakeAttack.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting Gun
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = Body;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	//UE_LOG(LogTemp, Warning, TEXT("Finish Fire!"));
	bIsFire = false;
}

void AGun::OnFire()
{
	if(CurrentAmmo <= 0 || !bCanReload || bIsFire)
		return;

	bIsFire = true;
	FireRay();
	CurrentAmmo--;

	if(UAnimInstance* AnimInstance = Cast<UAnimInstance>(FatherCharacter->GetMesh()->GetAnimInstance()))
	{
		if(FatherCharacter->bCanAim)
			AnimInstance->Montage_Play(Mother->AimFireMontage, Mother->FireSpeed);
		else
			AnimInstance->Montage_Play(Mother->FireMontage, Mother->FireSpeed);
	}
}

void AGun::OnReload()
{
	if(CurrentAmmo >= Mother->MaxAmmo || bIsFire || Brother->SubAmmo <= 0)
	{
		FatherCharacter->GetMesh()->GetAnimInstance()->StopAllMontages(0.2f);
		bCanReload = true;
		return;
	}
		
	
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
	int32 AmmoNeeded = Mother->MaxAmmo -CurrentAmmo;
	int32 AmmoToReload = FMath::Min(AmmoNeeded, Brother->SubAmmo);
	if(Brother->SubAmmo - AmmoToReload > Brother->SubMaxAmmo)
	{
		Brother->SubAmmo = 0;
	}
	// 탄약 갱신
	CurrentAmmo += AmmoToReload;
	Brother->SubAmmo -= AmmoToReload;
}


void AGun::EndReload()
{
	bCanReload = true;
}

void AGun::FireRay()
{
	FHitResult HitResult;

	// 레이 시작 지점
	FVector Start = FatherCharacter->GetCameraComponent()->GetComponentLocation();
    
	// 레이 끝 지점
	FVector End = Start + (FatherCharacter->GetActorForwardVector() * Mother->Distance);

	// 레이 트레이스 실행
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollsionLivingEntity))
	{
		// 충돌한 액터의 이름 출력
		UE_LOG(LogTemp, Display, TEXT("%s"), *HitResult.GetActor()->GetName());

		// 공격 처리
		if (IISTLTTakeAttack* TakeAttack = Cast<IISTLTTakeAttack>(HitResult.GetActor()))
		{
			TakeAttack->TakeAttack(EAttackType::BULLET, HitResult.GetActor(), Mother->Damage);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Fail Cast TakeAttack"));
		}
	}
}