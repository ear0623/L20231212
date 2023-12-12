// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThirdPersonMPProjectile.generated.h"

UCLASS()
class MYPROJECT3_API AThirdPersonMPProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThirdPersonMPProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed()override;

	UFUNCTION(Category ="Projectile")
	void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* othercomp, FVector NormalImpuls, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Cpmponents")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cpmponents")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cpmponents")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere,Category="Effects")
	class UParticleSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Damage")
	TSubclassOf<class UDamageType> DamageType;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Damage")
	float Damage;

};
