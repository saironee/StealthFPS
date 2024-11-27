// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/STLTReloadNotify.h"
#include "Characters/STLTPlayerCharacter.h"
#include "Gun/Gun.h"
#include "Interface/STLTEndReloadInterface.h"

void USTLTReloadNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(MeshComp)
	{
		ASTLTPlayerCharacter* PlayerCharacter = Cast<ASTLTPlayerCharacter>(MeshComp->GetOwner());
		if(PlayerCharacter)
		{
			if(ISTLTEndReloadInterface* Reload = Cast<ISTLTEndReloadInterface>(PlayerCharacter->MyGun))
			{
				Reload->EndReload();
			}
		}
	}
}
