#pragma once

#include <d3d11_4.h>			// directx 11 ver.4
#include <d3dcompiler.h>		// 쉐이더 컴파일러용 인터페이스

#include <EnginePlatform/EngineWindow.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "dxguid")

#pragma comment(lib, "DXGI")	// 모니터 정보 또는 그래픽카드 정보를 얻어오는 함수를 가지고 있는 라이브러리

// 설명 :
class UEngineGraphicDevice
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineGraphicDevice();
	ENGINEAPI ~UEngineGraphicDevice();

	// delete Function
	UEngineGraphicDevice(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice(UEngineGraphicDevice&& _Other) noexcept = delete;
	UEngineGraphicDevice& operator=(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice& operator=(UEngineGraphicDevice&& _Other) noexcept = delete;

	void CreateDeviceAndContext();

	void CreateBackBuffer(const UEngineWindow& _Window);

	IDXGIAdapter* GetHighPerFormanceAdapter();

	void Release();

	void ReleaseStart();

	void ReleaseEnd();

protected:

private:
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;
	IDXGISwapChain* SwapChain = nullptr;

	IDXGIAdapter* MainAdapter = nullptr;

	ID3D11Texture2D* DXBackBufferTexture = nullptr;
	ID3D11RenderTargetView* RTV = nullptr;
};

