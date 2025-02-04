#include "PreCompile.h"
#include "Monster.h"

#include <EngineCore/TimeEventComponent.h>

#include "Yoshi.h"

AMonster::AMonster()
{
	TimeEvent = CreateDefaultSubObject<UTimeEventComponent>();
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	AActor::BeginPlay();
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	Gravity(_DeltaTime);
}

bool AMonster::CheckForceColor(FVector _Force, UColor _Color)
{
	FVector NextPos = GetActorLocation() + _Force;
	UColor Color = GetWorld()->GetMainPawn<AYoshi>()->GetColor(NextPos);

	if (Color.operator==(_Color))
	{
		return true;
	}

	return false;
}

void AMonster::Gravity(float _DeltaTime)
{
	FVector GravityValue = GravityForce * _DeltaTime;

	if (CheckForceColor(GravityValue, UColor::BLACK))
	{
		AddActorLocation(GravityValue);
		GravityForce += FVector::DOWN * GravityPower * _DeltaTime;
	}
	else
	{
		GravityForce = FVector::ZERO;
	}
}

void AMonster::FallDown(float _DeltaTime)
{
	GravityForce = FVector::ZERO;
	AddActorLocation(FVector::DOWN * GravityPower * 0.5f * _DeltaTime);

	TimeEvent->AddEvent(2.0f, nullptr, std::bind(&AMonster::Off, this), false);
}

void AMonster::Off()
{
	this->Destroy();
}

