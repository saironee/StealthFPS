// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ReloadNotify.h"

void UReloadNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
}
