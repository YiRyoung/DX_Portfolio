#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>
#include "IContentsCore.h"
#include "Level.h"

UEngineWindow UEngineCore::MainWindow;
HMODULE UEngineCore::ContentsDLL = nullptr;
std::shared_ptr<IContentsCore> UEngineCore::Core;

std::shared_ptr<class ULevel> UEngineCore::NextLevel;
std::shared_ptr<class ULevel> UEngineCore::CurLevel = nullptr;

std::map<std::string, std::shared_ptr<class ULevel>> UEngineCore::LevelMap;

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

ENGINEAPI void UEngineCore::OpenLevel(std::string_view _Name)
{
	if (false == LevelMap.contains(_Name.data()))
	{
		MSGASSERT("������ ���� ������ �����Ϸ��� �߽��ϴ�." + std::string(_Name));
		return;
	}

	NextLevel = LevelMap[_Name.data()];
}

void UEngineCore::WindowInit(HINSTANCE _Instance)
{
	UEngineWindow::EngineWindowInit(_Instance);
	MainWindow.Open("MainWindow");
}

void UEngineCore::LoadContents(std::string_view _DllName)
{
	UEngineDirectory Dir;

	Dir.MoveParentToDirectory("Build");
	Dir.Move("bin/x64");

	// ���� ��Ȳ�� ���� ��� ����
#ifdef _DEBUG
	Dir.Move("Debug");
#else
	Dir.Move("Release");
#endif

	UEngineFile File = Dir.GetFile(_DllName);

	std::string FullPath = File.GetPathToString();

	ContentsDLL = LoadLibraryA(FullPath.c_str());

	if (nullptr == ContentsDLL)
	{
		MSGASSERT("������ ����� �ε��Ҽ��� �����ϴ�.");
		return;
	}

	INT_PTR(__stdcall * Ptr)(std::shared_ptr<IContentsCore>&) = (INT_PTR(__stdcall*)(std::shared_ptr<IContentsCore>&))GetProcAddress(ContentsDLL, "CreateContentsCore");

	if (nullptr == Ptr)
	{
		MSGASSERT("������ �ھ� ���ο� CreateContentsCoreDefine�� �������� �ʾҽ��ϴ�.");
		return;
	}

	Ptr(Core);

	if (nullptr == Core)
	{
		MSGASSERT("������ �ھ� ������ �����߽��ϴ�.");
		return;
	}
}

void UEngineCore::EngineFrame()
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelChangeEnd();
		}

		CurLevel = NextLevel;

		CurLevel->LevelChangeStart();
		NextLevel = nullptr;
	}

	CurLevel->Tick(0.0f);
	CurLevel->Render(0.0f);
}

void UEngineCore::EngineEnd()
{
	LevelMap.clear();
	//UEngineDebug::EndConsole();
}

std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string_view _Name)
{
	std::shared_ptr<ULevel> Ptr = std::make_shared<ULevel>();
	Ptr->SetName(_Name);

	LevelMap.insert({ _Name.data(), Ptr });

	return Ptr;
}

void UEngineCore::EngineStart(HINSTANCE _Instance, std::string_view _DllName)
{
	UEngineDebug::LeakCheck();

	WindowInit(_Instance);

	LoadContents(_DllName);

	UEngineWindow::WindowMessageLoop(
		[]()
		{
			//UEngineDebug::StartConsole();
			UEngineInitData Data;
			Core->EngineStart(Data);

			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);
			// ������ �� �ϰ� ���� ��
		},
		[]()
		{
			// ������ ���ư� �� �ϰ� ���� ��
			EngineFrame();
		},
		[]()
		{
			// ������ ������ �� �ϰ� ���� ��
			EngineEnd();
		});	
}