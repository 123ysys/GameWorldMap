// Fill out your copyright notice in the Description page of Project Settings.


#include "GWGlobalMapWidgetMiddleware.h"

void UGWGlobalMapWidgetMiddleware::OnMapDragStart(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	IsDragging = true;

	DragSourceMouseAbsoluteCoordinates = FVector2D(OffsetX, OffsetY) + CalculateAbsoluteOffset(InGeometry, InMouseEvent);
}

void UGWGlobalMapWidgetMiddleware::OnMapDragEnd(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	IsDragging = false;
}

void UGWGlobalMapWidgetMiddleware::OnMapDragging(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (IsDragging)
	{
		FVector2D AbsoluteOffset = CalculateAbsoluteOffset(InGeometry, InMouseEvent);
		UpdateOffset(DragSourceMouseAbsoluteCoordinates, AbsoluteOffset);
	}
}

void UGWGlobalMapWidgetMiddleware::OnMapScale(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!IsDragging)
	{
		DragSourceMouseAbsoluteCoordinates = FVector2D(OffsetX, OffsetY) + CalculateAbsoluteOffset(InGeometry, InMouseEvent);
	}
	Scalar += InMouseEvent.GetWheelDelta() / 5;
	Scalar = FMath::Clamp(Scalar, 0, 10);
	FVector2D AbsoluteOffset = CalculateAbsoluteOffset(InGeometry, InMouseEvent);
	UpdateOffset(DragSourceMouseAbsoluteCoordinates, AbsoluteOffset);
}

FVector2D UGWGlobalMapWidgetMiddleware::CalculateAbsoluteOffset(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FVector2D MousePosition = InMouseEvent.GetScreenSpacePosition();
	FVector2D TopLeft = InGeometry.GetAbsolutePositionAtCoordinates(FVector2D(0, 0));
	return (MousePosition - TopLeft) * Scalar / InGeometry.GetLocalSize();
}

void UGWGlobalMapWidgetMiddleware::UpdateOffset(const FVector2D& InAbsoluteCoordinates, const FVector2D& InAbsoluteOffset)
{
	FVector2D Result = (InAbsoluteCoordinates - InAbsoluteOffset).ClampAxes(0, 1 / Scalar);
	OffsetX = Result.X;
	OffsetY = Result.Y;

	UpdateViewport();
}