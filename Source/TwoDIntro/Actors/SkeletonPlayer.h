//Copyright © 2023 Pluz21(TVL).All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

#include "PaperZDCharacter.h"

#include "SkeletonPlayer.generated.h"

UCLASS()

class TWODINTRO_API ASkeletonPlayer : public APaperZDCharacter
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FJumpEvent);

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FJumpEvent onJump;

	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkeletonPlayer();

	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputMappingContext> mappingContext = nullptr;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> inputToMove = nullptr;
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> inputToJump = nullptr;
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> inputToAttack = nullptr;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	float moveSpeed = 200.f;
	UPROPERTY(EditAnywhere, Category = "Inputs")
	bool canChangeRotation = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init();
	void InitInputs();

	void SetupPlayerInputComponent(UInputComponent* _playerInputComponent);
	
	// Inputs

	void Move(const FInputActionValue& _value);
	void Jump();
	UFUNCTION(BlueprintCallable)
	void ChangeRotation();
	UFUNCTION(BlueprintCallable)
	void CheckVelocity();
	UFUNCTION(BlueprintCallable)
	void SetCanChangeRotation(bool _value);
	UFUNCTION(BlueprintCallable)
	void UpdatePlayerRotation();
};
