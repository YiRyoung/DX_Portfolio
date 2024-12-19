#pragma once

#include <EnginePlatform/PreCompile.h>

#include "EngineCore.h"
#include "Pawn.h"
#include "GameMode.h"

#pragma comment(lib, "EngineBase.lib")
#pragma comment(lib, "EnginePlatform.lib")

#include <wrl.h>
#include <d3d11_4.h>			// directx 11 ver.4
#include <d3dcompiler.h>		// 쉐이더 컴파일러용 인터페이스

#include <EnginePlatform/EngineWindow.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "dxguid")

#pragma comment(lib, "DXGI")