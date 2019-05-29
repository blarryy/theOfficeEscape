// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDrawer.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDrawerEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEOFFICEESCAPE_API UOpenDrawer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDrawer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintAssignable)
	FDrawerEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
	FDrawerEvent OnClose;
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 3.f;
	float LastDoorOpenTime;
	bool DrawerClosed = true;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
