#pragma once

#include "Components/ActorComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "escapeTheRoomBlueprintFunctionLibrary.generated.h"

UCLASS()
class ESCAPETHEROOM_API UescapeTheRoomBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
    
public:
    /**Dynamically create a UActorComponent on a given actor during runtime or outside of the constructor.**/
    UFUNCTION(BlueprintCallable, Category="Actor|ActorComponent")
    static UActorComponent* RequireComponent(AActor* IntendedOwner, TSubclassOf<UActorComponent> requiredComponentClass, bool &classFound);

    /**This templated function is not available for use in blueprints but makes for a nice helper in C++**/
    template<typename T>
    FORCEINLINE static T* RequireComponentCast(AActor* IntendedOwner, bool &classFound) { return Cast<T>(RequireComponent(IntendedOwner, T::StaticClass(), classFound)); }

};