// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMods/STLTGameMode.h"

#include "Characters/STLTPlayerCharacter.h"

ASTLTGameMode::ASTLTGameMode()
{
	ConstructorHelpers::FClassFinder<ASTLTPlayerCharacter>
		PlayerRef(TEXT("/Game/Blueprint/Player/BP_STLTPlayer.BP_STLTPlayer_C"));
	if(PlayerRef.Class != nullptr)
		DefaultPawnClass = PlayerRef.Class;
}
