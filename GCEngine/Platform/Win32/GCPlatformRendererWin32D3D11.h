#pragma once
#include "../GCPlatformRenderer.h"
#include <d3d11.h>
#include <dxgi1_2.h>

class GCPlatformRendererWin32D3D11 final : public IGCPlatformRenderer
{
public:
	explicit GCPlatformRendererWin32D3D11(HWND InWindowHandle);
	bool Initialize(int Width, int Height) override;
	void Update() override;
	void Shutdown() override;

private:
	HWND WindowHandle;
	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;
	ID3D11RenderTargetView* RenderTargetView;
	IDXGISwapChain1* SwapChain;
};