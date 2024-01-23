//Copyright © 2023 Pluz21(TVL).All rights reserved.

#include "SkeletonPlayer.h"

#include "PaperFlipbookComponent.h"


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ASkeletonPlayer::ASkeletonPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkeletonPlayer::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

// Called every frame
void ASkeletonPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//CheckVelocity();
	//ChangeRotation();
	UpdatePlayerRotation();
}

void ASkeletonPlayer::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Paper character init"));
	InitInputs();
}

void ASkeletonPlayer::InitInputs()
{
	ULocalPlayer* _myPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();
	if (!_myPlayer)return;
	UEnhancedInputLocalPlayerSubsystem* _inputSystem = _myPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!_inputSystem)return;
	_inputSystem->AddMappingContext(mappingContext, 0);
}

void ASkeletonPlayer::Move(const FInputActionValue& _value)
{
	UE_LOG(LogTemp, Warning, TEXT("Fired Move function"));

	if (!inputToMove)return;
	float _delta = GetWorld()->DeltaTimeSeconds;
	const FVector _fwd = GetActorForwardVector();
	const FVector2D _movementValue = _value.Get<FVector2D>(); //* _delta * moveSpeed
	const float _forwardMovementValue = _movementValue.X * _delta * moveSpeed;
	//forwardInputValue = _movementValue.X;
	AddMovementInput(_fwd, _forwardMovementValue);
}

void ASkeletonPlayer::Jump()
{
	Super::Jump();
	onJump.Broadcast();
}

void ASkeletonPlayer::ChangeRotation()
{
	if (canChangeRotation)
	{
	FRotator _currentRotation = GetActorRotation();
	FRotator _newRotation = _currentRotation + FRotator(_currentRotation.Pitch,
		180, _currentRotation.Roll);
	SetActorRelativeRotation(_newRotation);
	}

}

void ASkeletonPlayer::CheckVelocity()
{
	float _velocity = GetVelocity().X;
	UE_LOG(LogTemp, Warning, TEXT("velocity on X is : %f"), _velocity);
	bool _isLowerThanZero = FMath::IsNearlyEqual(_velocity, -0.1f);
	if (_velocity < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("lower than 0"));

		SetCanChangeRotation(true);
	}
	else
	{
		SetCanChangeRotation(false);
	}
}

void ASkeletonPlayer::SetCanChangeRotation(bool _value)
{
	canChangeRotation = _value;
}

void ASkeletonPlayer::UpdatePlayerRotation()
{
	float _velocityX = GetVelocity().X;
	UPaperFlipbookComponent* _sprite = GetSprite();
	if (!_sprite)return;
	if (_velocityX > 0)
	{
		_sprite->SetRelativeRotation(FRotator::ZeroRotator);
	}
	if (_velocityX < 0)
	{
		_sprite->SetRelativeRotation(FRotator(0, 180,0));

	}
			
}



void ASkeletonPlayer::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);
	UEnhancedInputComponent* _myInputCompo = Cast<UEnhancedInputComponent>(_playerInputComponent);

	if (!_myInputCompo)
	{
		UE_LOG(LogTemp, Warning, TEXT("Faile to find input component"));
		return;
	}
	_myInputCompo->BindAction(inputToMove, ETriggerEvent::Triggered, this, &ASkeletonPlayer::Move);
	_myInputCompo->BindAction(inputToJump, ETriggerEvent::Triggered, this, &ASkeletonPlayer::Jump);

}