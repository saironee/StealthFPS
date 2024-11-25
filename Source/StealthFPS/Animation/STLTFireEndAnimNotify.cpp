// Fill out your copyright notice in the Description page of Project Settings.


#include "STLTFireEndAnimNotify.h"
#include "Interface/STLTFireEndInterface.h"
#include "Characters/STLTPlayerCharacter.h"
#include "Gun/Gun.h"

void USTLTFireEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(MeshComp)
	{
		ASTLTPlayerCharacter* PlayerCharacter = Cast<ASTLTPlayerCharacter>(MeshComp->GetOwner());
		if(PlayerCharacter)
		{
			if(ISTLTFireEndInterface* FireEnd = Cast<ISTLTFireEndInterface>(PlayerCharacter->MyGun))
			{
				FireEnd->FireEnd();
			}
		}
	}
}
