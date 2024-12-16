#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/Level.h>

CreateContentsCoreDefine(UContentsCore);

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1020, 680 };

	std::shared_ptr<ULevel> Level = UEngineCore::CreateLevel("Title");
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}