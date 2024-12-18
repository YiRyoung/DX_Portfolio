#pragma once

#include <d3d11_4.h>			// directx 11 ver.4
#include <d3dcompiler.h>		// ���̴� �����Ϸ��� �������̽�

#include <EnginePlatform/EngineWindow.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "dxguid")

#pragma comment(lib, "DXGI")	// ����� ���� �Ǵ� �׷���ī�� ������ ������ �Լ��� ������ �ִ� ���̺귯��

// ���� :
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

	ENGINEAPI ID3D11Device* GetDevice()
	{
		return Device;
	}

	ENGINEAPI ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

protected:

private:
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;
	IDXGISwapChain* SwapChain = nullptr;

	IDXGIAdapter* MainAdapter = nullptr;

	ID3D11Texture2D* DXBackBufferTexture = nullptr;
	ID3D11RenderTargetView* RTV = nullptr;
};

