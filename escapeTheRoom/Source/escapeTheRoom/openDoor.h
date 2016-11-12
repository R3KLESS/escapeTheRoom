// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "openDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API UopenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UopenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void openDoor();
	void closeDoor();

private:
	UPROPERTY(VisibleAnywhere)
		float doorOpenAngle = 90.f;
		float doorCloseAngle = 0.f;
	
	UPROPERTY(EditAnywhere)
		ATriggerVolume* doorPressurePlate;

	UPROPERTY(EditAnywhere)
		bool isDoorOpen = false;

	UPROPERTY(EditAnywhere)
		float doorCloseDelay = 1.f;

	UPROPERTY(EditAnywhere)
		float lastDoorOpenTime;


		AActor* actorThatCanOpenDoor;
		AActor* owner;

};
