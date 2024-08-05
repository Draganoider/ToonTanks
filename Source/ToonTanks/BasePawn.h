// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	virtual void Fire();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

protected:

	void RotateTurret(FVector LookAtTarget);

	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	

	
	UPROPERTY(EditDefaultsOnly, Category = "TurretSpeed");
	float TurretRotationSpeed = 30.f;

	

	UPROPERTY(EditAnywhere, Category = "Combat1")
	class UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Combat1")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat1")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
