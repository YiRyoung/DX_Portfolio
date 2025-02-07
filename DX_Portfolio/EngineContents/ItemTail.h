#pragma once
#include <EngineCore/Actor.h>

// ���� :
class AItemTail : public AActor
{
public:
	// constrcuter destructer
	AItemTail();
	~AItemTail();

	// delete Function
	AItemTail(const AItemTail& _Other) = delete;
	AItemTail(AItemTail&& _Other) noexcept = delete;
	AItemTail& operator=(const AItemTail& _Other) = delete;
	AItemTail& operator=(AItemTail&& _Other) noexcept = delete;

protected:

private:
	std::vector<AActor> Item;
};

