// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GWGlobalMapWidgetMiddleware.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GAMEWORLDMAP_API UGWGlobalMapWidgetMiddleware : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "GameWorldMap|MapCanvas")
	void OnMapDragStart(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	UFUNCTION(BlueprintCallable, Category = "GameWorldMap|MapCanvas")
	void OnMapDragEnd(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	UFUNCTION(BlueprintCallable, Category = "GameWorldMap|MapCanvas")
	void OnMapDragging(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	UFUNCTION(BlueprintCallable, Category = "GameWorldMap|MapCanvas")
	void OnMapScale(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "GameWorldMap|MapCanvas")
	void UpdateViewport();

	/** MapCanvas */
	UPROPERTY(BlueprintReadOnly, Category = "GameWorldMap|MapCanvas")
	float OffsetX = 0;
	UPROPERTY(BlueprintReadOnly, Category = "GameWorldMap|MapCanvas")
	float OffsetY = 0;
	UPROPERTY(BlueprintReadOnly, Category = "GameWorldMap|MapCanvas")
	float Scalar = 1;

private:
	void UpdateOffset(const FVector2D& InAbsoluteCoordinates, const FVector2D& InAbsoluteOffset);
	FVector2D CalculateAbsoluteOffset(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	bool IsDragging = false;
	FVector2D DragSourceMouseAbsoluteCoordinates;
};
