#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h" // UUserWidget 관련 헤더 포함
#include "STLTPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHFPS_API ASTLTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// 위젯 클래스 참조
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MainWidgetClass;

	// 현재 표시 중인 위젯
	UPROPERTY()
	UUserWidget* CurrentWidget;

	// UI 초기화
	virtual void BeginPlay() override;
};
