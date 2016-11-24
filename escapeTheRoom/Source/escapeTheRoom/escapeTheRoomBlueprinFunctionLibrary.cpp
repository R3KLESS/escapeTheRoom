#include "escapeTheRoom.h"
#include "escapeTheRoomBlueprintFunctionLibrary.h"


int32 nameIndex = 0;

/**
** Use TSubclassOf to guarantee that the desired class of the component to construct is actually a UActorComponent child class. Also, it helps Blueprints help you pick the correct UClass type - MH
**/
UActorComponent* UescapeTheRoomBlueprintFunctionLibrary::RequireComponent(AActor* IntendedComponentOwner, TSubclassOf<UActorComponent> requiredComponentClass)
{
	UActorComponent* ResultComponent = nullptr;
	UClass* ComponentClass = *requiredComponentClass;
	if (ComponentClass && IntendedComponentOwner)
	{
		ResultComponent = IntendedComponentOwner->FindComponentByClass(ComponentClass);
		if (ResultComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found First Component %s of Class %s in Actor %s"), *ResultComponent->GetName(), *ComponentClass->GetName(), *IntendedComponentOwner->GetName());

			FName name = *ComponentClass->GetName();

			FString nameIncrementString = name.ToString();

			nameIncrementString.Append("_");
			nameIncrementString.Append(FString::FromInt(nameIndex));

			FName newCompName = FName(*nameIncrementString);

			nameIndex = nameIndex + 1;

			#if WITH_EDITOR
			IntendedComponentOwner->Modify();
			#endif
			// Construct the new component and attach as needed
			UActorComponent* NewInstanceComponent = NewObject<UActorComponent>(IntendedComponentOwner, ComponentClass, newCompName);
			if (NewInstanceComponent)
			{
				// Add to SerializedComponents array so it gets saved
				IntendedComponentOwner->AddInstanceComponent(NewInstanceComponent);
				// Fire off the event that a Component was created
				NewInstanceComponent->OnComponentCreated();
				// Register the Component so that it is active in game code
				NewInstanceComponent->RegisterComponent();

				#if WITH_EDITOR
				IntendedComponentOwner->RerunConstructionScripts();
				#endif

				ResultComponent = NewInstanceComponent;

				UE_LOG(LogTemp, Warning, TEXT("Created required Component %s of type %s on Actor %s"), *ResultComponent->GetName(), *ResultComponent->GetClass()->GetName(), *IntendedComponentOwner->GetName());
			}

	return ResultComponent;

		}
		else
		{
			nameIndex = 0;

			FName name = *ComponentClass->GetName();

			#if WITH_EDITOR
			IntendedComponentOwner->Modify();
#endif
			// Construct the new component and attach as needed
			UActorComponent* NewInstanceComponent = NewObject<UActorComponent>(IntendedComponentOwner, ComponentClass, name);
			if (NewInstanceComponent)
			{
				// Add to SerializedComponents array so it gets saved
				IntendedComponentOwner->AddInstanceComponent(NewInstanceComponent);
				// Fire off the event that a Component was created
				NewInstanceComponent->OnComponentCreated();
				// Register the Component so that it is active in game code
				NewInstanceComponent->RegisterComponent();

#if WITH_EDITOR
				IntendedComponentOwner->RerunConstructionScripts();
#endif

				ResultComponent = NewInstanceComponent;

				UE_LOG(LogTemp, Warning, TEXT("Created required Component %s of type %s on Actor %s"), *ResultComponent->GetName(), *ResultComponent->GetClass()->GetName(), *IntendedComponentOwner->GetName());
			}
		}
	}

	return ResultComponent;
}