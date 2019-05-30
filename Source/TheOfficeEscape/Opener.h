// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Opener.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEOFFICEESCAPE_API UOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpener();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	float Reach = 125.f;
	UInputComponent* InputComponent = nullptr;
	FVector GetReachLineStart();
	FVector GetReachLineEnd();
	void Open();
	void SetUpInputComponent();
	const FHitResult GetFirstPhysicsBodyInReach();
	


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
