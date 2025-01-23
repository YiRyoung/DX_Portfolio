#include "PreCompile.h"
#include "ShyGuy.h"

#include <EngineBase/EngineRandom.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>
#include <EngineCore/TimeEventComponent.h>

AShyGuy::AShyGuy()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetAutoScaleRatio(3.0f);
	Renderer->SetSprite("Shy Guys.png", 0);

	TimeEvent = CreateDefaultSubObject<UTimeEventComponent>();
}

AShyGuy::~AShyGuy()
{
}

void AShyGuy::BeginPlay()
{
	AMonster::BeginPlay();
	ChangeState(EMonsterState::IDLE);
	SetAnimation();
	SetCollision();
}

void AShyGuy::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
}

void AShyGuy::SetCollision()
{
	MonsterBodyCollision = CreateDefaultSubObject<UCollision>();
	MonsterBodyCollision->SetupAttachment(RootComponent);
	MonsterBodyCollision->SetCollisionProfileName("MonsterHeadCollision");
	MonsterBodyCollision->SetScale3D({ 48.0f , 57* 0.3f });
	MonsterBodyCollision->SetRelativeLocation({ 0.0f, 57 * 0.8f });

	MonsterHeadCollision = CreateDefaultSubObject<UCollision>();
	MonsterHeadCollision->SetupAttachment(RootComponent);
	MonsterHeadCollision->SetCollisionProfileName("MonsterBodyCollision");
	MonsterHeadCollision->SetScale3D({ 48.0f, 57 * 0.7f });
	MonsterHeadCollision->SetRelativeLocation({ 0.0f, 57 * 0.3f });
}

void AShyGuy::SetAnimation()
{
	Renderer->CreateAnimation("Walk", "Shy Guys.png", 0, 4, 0.2f);
}

void AShyGuy::ChangeAnimDir()
{
	if (CurMonsterState != EMonsterState::IDLE)
	{
		if (TimeEvent != nullptr)
		{
			TimeEvent = nullptr;
			return;
		}
	}

	FVector RotationValue = RootComponent->GetTransformRef().WorldScale;

	if (RotationValue.X > 0)
	{
		RootComponent->SetScale3D({ -1, 1, 1 });
	}
	else if (RotationValue.X < 0)
	{
		RootComponent->SetScale3D({ 1, 1, 1 });
	}

	TimeEvent->AddEvent(1.0f, nullptr, std::bind(&AShyGuy::ChangeAnimDir, this), false);

}

void AShyGuy::IdleStart()
{
	Renderer->SetSprite("Shy Guys.png", 0);
	TimeEvent->AddEvent(1.0f, nullptr, std::bind(&AShyGuy::ChangeAnimDir, this), false);
}

void AShyGuy::WalkStart()
{
	Renderer->ChangeAnimation("Walk");
}

void AShyGuy::Walk(float _DeltaTime)
{
	
}
