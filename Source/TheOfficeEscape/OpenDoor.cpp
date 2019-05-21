// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UOpenDoor::OpenDoor()
{
	FRotator NewRotation = FRotator(0.0f, openAngle, 0.0f);
	if (!Owner) {return;}
	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor()
{
	FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
	if (!Owner) {return;}
	Owner->SetActorRotation(NewRotation);
}

// Caled when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate(){
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate){return 0.f;}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* Actor : OverlappingActors)
		{
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	return TotalMass;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOfActorsOnPlate() > 29.f){	//TODO: make it into a parameter
			OpenDoor();
			LastDoorOpenTime = GetWorld() -> GetTimeSeconds();
	}
	//check if it's time to close the door
	if (GetWorld() -> GetTimeSeconds() > LastDoorOpenTime + DoorCloseDelay){
		CloseDoor();
	}
}

