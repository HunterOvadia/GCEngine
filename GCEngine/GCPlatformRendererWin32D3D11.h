#pragma once
#include "GCPlatformRenderer.h"
#include <d3d11.h>
#include <dxgi1_2.h>

class GCPlatformRendererWin32D3D11 : public IGCPlatformRenderer
{
public:
	GCPlatformRendererWin32D3D11(HWND InWindowHandle);
	virtual bool Initialize(int Width, int Height) override;
	virtual void Update() override;
	virtual void Shutdown() override;

private:
	HWND WindowHandle;
	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;
	ID3D11RenderTargetView* RenderTargetView;
	IDXGISwapChain1* SwapChain;
};