#pragma once
#include "Monster.h"

// ���� :
class AShyGuy : public AMonster
{
public:
	// constrcuter destructer
	AShyGuy();
	~AShyGuy();

	// delete Function
	AShyGuy(const AShyGuy& _Other) = delete;
	AShyGuy(AShyGuy&& _Other) noexcept = delete;
	AShyGuy& operator=(const AShyGuy& _Other) = delete;
	AShyGuy& operator=(AShyGuy&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class UTimeEventComponent> TimeEvent;
	void SetAnimation() override;

	void ChangeIdleAnim();
	void SetIdleAnim();

	void IdleStart() override;
	void Idle(float _DeltaTime);
};

