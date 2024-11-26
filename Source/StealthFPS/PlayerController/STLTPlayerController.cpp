#include "PlayerController/STLTPlayerController.h"
#include "Blueprint/UserWidget.h"

ASTLTPlayerController::ASTLTPlayerController()
{
	ConstructorHelpers::FClassFinder<UUserWidget>
		WidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UserWidget/WBP_Main.WBP_Main'"));
	if(WidgetRef.Class != nullptr)
		MainWidgetClass = WidgetRef.Class;
}

void ASTLTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	

	// 위젯 클래스가 유효한지 확인
	if (MainWidgetClass)
	{
		// 위젯 생성
		CurrentWidget = CreateWidget<UUserWidget>(this, MainWidgetClass);
		if (CurrentWidget)
		{
			// 위젯 화면에 추가
			CurrentWidget->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("UI Initialized: %s"), *CurrentWidget->GetName());
		}
	}
}
