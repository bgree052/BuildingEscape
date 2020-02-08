// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen2;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose2;

private:
	void CloseDoor();

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlatePurple = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlateGreen = nullptr;

	UPROPERTY(EditAnywhere)
	AActor *GreenChair = nullptr;

	UPROPERTY(EditAnywhere)
	AActor *PurpleTable = nullptr;

	UPROPERTY(EditAnywhere)
	float TriggerMass;

	UPROPERTY(EditAnywhere)
	int RoomNumber;

	//The Owning Door
	AActor *Owner = nullptr;

	float GetTotalMassOfActorsOnPlate();
	bool CheckBothPlatesAreCovered();
	bool CheckCorrectObjectOnPlate(AActor *DesiredObject);
};
