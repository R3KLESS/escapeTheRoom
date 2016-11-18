// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API Ugrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Ugrabber();

	// Called when the game starts
	virtual void BeginPlay() override;

	/**Overrides from the UObject Base Class**/
	virtual void PostInitProperties() override;
	/**End Overrides from the UObject Base Class**/
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;	

private:
	
	// how far ahead of the player can the grabber component reach.
	float grabberReach = 100.f;

	/* create a new pointer to a physicsHandlerComponent
	give it the VisibleAnywhere property specifier
	so that we can edit its properties in the editor.

	We are marking this as Transient since the real owner is the Actor that is the Owner of this Component. And we want to fetch this component whenever we load this object - MH**/
	UPROPERTY(VisibleAnywhere, Transient)
	UPhysicsHandleComponent* createdPhysicsHandleComponent;

	

	//UPROPERTY(EditAnywhere)
		//UClass* testClass =nullptr;

};
