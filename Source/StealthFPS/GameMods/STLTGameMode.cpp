#include "GameMods/STLTGameMode.h"
#include "Characters/STLTPlayerCharacter.h"
#include "PlayerController/STLTPlayerController.h"

ASTLTGameMode::ASTLTGameMode()
{
	// Default Pawn 설정
	ConstructorHelpers::FClassFinder<ASTLTPlayerCharacter>
		PlayerRef(TEXT("/Game/Blueprint/Player/BP_STLTPlayer.BP_STLTPlayer_C"));
	if (PlayerRef.Class != nullptr)
	{
		DefaultPawnClass = PlayerRef.Class;
	}

	// Player Controller 설정
	ConstructorHelpers::FClassFinder<APlayerController>
		ControllerRef(TEXT("/Game/PlayerController/BP_PlayerController.BP_PlayerController_C"));
	if (ControllerRef.Class != nullptr)
	{
		PlayerControllerClass = ControllerRef.Class;
	}
}
