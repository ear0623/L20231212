// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersonMPCharacter.generated.h"

UCLASS()
class MYPROJECT3_API AThirdPersonMPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersonMPCharacter();
	//Property Replication
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//
	UPROPERTY(EditDefaultsOnly, Category="Health")
	float MaxHealth;
	UPROPERTY(ReplicatedUsing=OnRep_CurrentHealth)
	float CurrentHealth;
	UFUNCTION()
	void OnRep_CurrentHealth();
	void OnHealthUpdate();

public:
	UFUNCTION(BlueprintPure,Category="Health")
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable,Category="Health")
	void SetCurrentHealth(float HealthValue);

	UFUNCTION(BlueprintPure,Category="Health")
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable,Category="Health")
	float TakeDamage(float DageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;


};
