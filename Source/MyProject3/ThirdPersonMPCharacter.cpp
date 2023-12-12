// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonMPCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

// Sets default values
AThirdPersonMPCharacter::AThirdPersonMPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

}

void AThirdPersonMPCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//
	DOREPLIFETIME(AThirdPersonMPCharacter, CurrentHealth);
}

// Called when the game starts or when spawned
void AThirdPersonMPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThirdPersonMPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThirdPersonMPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AThirdPersonMPCharacter::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

void AThirdPersonMPCharacter::OnHealthUpdate()
{
	//
	if (IsLocallyControlled())
	{
		FString HealthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, HealthMessage);

		if (CurrentHealth <=0)
		{
			FString DeathMessage = FString::Printf(TEXT("You have been killed."));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, DeathMessage);
		}
	}
	//
	if (GetLocalRole() == ROLE_Authority)
	{
		FString HealthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, HealthMessage);
	}
	//
	/*
	* ����� �Ǵ� ����� ����� �߻��ϴ� Ư���Լ� ��� ��ġ
	*/
}

void AThirdPersonMPCharacter::SetCurrentHealth(float HealthValue)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		CurrentHealth == FMath::Clamp(HealthValue, 0.0f, MaxHealth);
		OnHealthUpdate();
	}
}

float AThirdPersonMPCharacter::TakeDamage(float DamageTaken, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = CurrentHealth - DamageTaken;
	SetCurrentHealth(DamageApplied);
	return DamageApplied;
}

