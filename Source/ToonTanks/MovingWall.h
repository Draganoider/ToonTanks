// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingWall.generated.h"

UCLASS()
class TOONTANKS_API AMovingWall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovingWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *WallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	FVector EndLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	FVector Offset;

	float CurrentTime;
	bool bMovingForward; // Новая переменная для отслеживания направления движения

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
