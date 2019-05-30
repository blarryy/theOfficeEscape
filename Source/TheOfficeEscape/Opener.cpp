// Fill out your copyright notice in the Description page of Project Settings.

#include "Opener.h"


// Sets default values for this component's properties
UOpener::UOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

FVector UOpener::GetReachLineEnd(){
	//Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	return LineTraceEnd;
}

FVector UOpener::GetReachLineStart(){
	//Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}


const FHitResult UOpener::GetFirstPhysicsBodyInReach(){
	//Ray-cast out to reach distance
	FHitResult Hit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit){
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	}
	return Hit;
}

void UOpener::Open(){
	UE_LOG(LogTemp, Warning, TEXT("E Pressed!"));
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	Default_Pawn_BP* pawn = Cast<Default_Pawn_BP>(ActorHit);
	// auto OpenDrawer = ComponentToGrab -> GetOwner()-> GetDefaultSubobjectByName(TEXT("OpenDrawer"));
	// if (ActorHit != nullptr){
	// 		PhysicsHandle->GrabComponent(
	// 		ComponentToGrab,
	// 		NAME_None,
	// 		ComponentToGrab->GetOwner()->GetActorLocation(),
	// 		true //allow rotation
	// 	);
	// }
}


void UOpener::SetUpInputComponent(){
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent){
		UE_LOG(LogTemp, Warning, TEXT("Input component reporting to duty!"));
	}
	InputComponent -> BindAction("Open", IE_Pressed, this, &UOpener::Open);
}

// Called when the game starts
void UOpener::BeginPlay()
{
	Super::BeginPlay();
	SetUpInputComponent();
	// ...
	
}


// Called every frame
void UOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

