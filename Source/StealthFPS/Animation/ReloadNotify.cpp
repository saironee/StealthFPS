// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ReloadNotify.h"
#include "Interface/IReloadInterface.h"
#include "Characters/STLTPlayerCharacter.h"
#include "Gun/Gun.h"

void UReloadNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(MeshComp)
	{
		ASTLTPlayerCharacter* PlayerCharacter = Cast<ASTLTPlayerCharacter>(MeshComp->GetOwner());
		if(PlayerCharacter)
		{
			if(IIReloadInterface* ReloadAmmo = Cast<IIReloadInterface>(PlayerCharacter->MyGun))
			{
				ReloadAmmo->Reload();
			}
		}
	}
}
