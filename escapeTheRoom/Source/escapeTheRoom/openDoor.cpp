// Fill out your copyright notice in the Description page of Project Settings.

#include "escapeTheRoom.h"
#include "openDoor.h"


// Sets default values for this component's properties
UopenDoor::UopenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UopenDoor::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
	// when the game begins find the pawn that was created in the world
	actorThatCanOpenDoor = GetWorld()->GetFirstPlayerController()->GetPawn();

	//test DELETE ME

}

// function to open the door in the scene
void UopenDoor::openDoor()
{
	// set the doors new rotation so that it opens
	owner->SetActorRotation(FRotator(0.f, doorOpenAngle, 0.f));
	isDoorOpen = true;
	
}

void UopenDoor::closeDoor()
{	
	// set the doors new rotation so that it closes
	owner->SetActorRotation(FRotator(0.f, doorCloseAngle, 0.f));
	isDoorOpen = false;

	UE_LOG(LogTemp, Warning, TEXT ("closeDoor function has been called"));

}


// Called every frame
void UopenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// poll the trigger volume
	if (doorPressurePlate->IsOverlappingActor(actorThatCanOpenDoor))
	{
		/* if the actorThatCanOpenDoor is inside the trigger volume
		then call the open door function */
		openDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

		if ( GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay && isDoorOpen)
		{
			closeDoor();
		}

}

