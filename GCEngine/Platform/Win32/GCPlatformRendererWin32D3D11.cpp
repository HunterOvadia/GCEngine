#include "GCPlatformRendererWin32D3D11.h"
#include "GCPlatformWin32.h"

GCPlatformRendererWin32D3D11::GCPlatformRendererWin32D3D11(const HWND InWindowHandle) 
	: WindowHandle(InWindowHandle)
	, Device(nullptr)
	, DeviceContext(nullptr)
	, RenderTargetView(nullptr)
	, SwapChain(nullptr)
{
}

bool GCPlatformRendererWin32D3D11::Initialize(const int Width, const int Height)
{
	bool Result = true;

	constexpr D3D_FEATURE_LEVEL FeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	int Flags = 0;
#if GC_DEBUG
	Flags = D3D11_CREATE_DEVICE_DEBUG;
#endif
	
	HR_CHECK(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, Flags, FeatureLevels, ARRAY_SIZE(FeatureLevels), D3D11_SDK_VERSION, &Device, nullptr, &DeviceContext));
	if (Device)
	{
		IDXGIDevice2* DXGIDevice2 = nullptr;
		IDXGIFactory2* DXGIFactory2 = nullptr;
		IDXGIAdapter2* DXGIAdapter = nullptr;
		Device->QueryInterface(__uuidof(IDXGIDevice2), reinterpret_cast<void**>(&DXGIDevice2));
	
		if (DXGIDevice2)
		{
			DXGIDevice2->GetParent(_uuidof(IDXGIAdapter2), reinterpret_cast<void**>(&DXGIAdapter));
			SAFE_RELEASE(DXGIDevice2);
		}
	
		if (DXGIAdapter)
		{
			DXGIAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&DXGIFactory2));
			SAFE_RELEASE(DXGIAdapter);
		}
	
		if (DXGIFactory2)
		{
			DXGI_SWAP_CHAIN_DESC1 SwapChainDesc = {};
			SwapChainDesc.Width = GetSystemMetrics(SM_CXSCREEN);
			SwapChainDesc.Height = GetSystemMetrics(SM_CYSCREEN);
			SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			SwapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			SwapChainDesc.SampleDesc.Count = 1;
			SwapChainDesc.BufferCount = 2;
			SwapChainDesc.Scaling = DXGI_SCALING_NONE;
			SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	
			HR_CHECK(DXGIFactory2->CreateSwapChainForHwnd(Device, WindowHandle, &SwapChainDesc, nullptr, nullptr, &SwapChain));
			SAFE_RELEASE(DXGIFactory2);
		}
	
		ID3D11Texture2D* BackBuffer = nullptr;
		HR_CHECK(SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer)));
		if (BackBuffer)
		{
			D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;
			RTVDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
			RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			RTVDesc.Texture2D.MipSlice = 0;
	
			HR_CHECK(Device->CreateRenderTargetView(BackBuffer, &RTVDesc, &RenderTargetView));
			SAFE_RELEASE(BackBuffer);
		}
	
		DeviceContext->OMSetRenderTargets(1, &RenderTargetView, 0);
	
		D3D11_VIEWPORT Viewport = {};
		Viewport.Width = Width;
		Viewport.Height = Height;
		Viewport.MaxDepth = 1.0f;
		DeviceContext->RSSetViewports(1, &Viewport);
		Result = true;
	}
		
	
	return Result;
}

void GCPlatformRendererWin32D3D11::Update()
{
	constexpr float Color[4] = { 0.09f, 0.09f, 0.1f, 1.0f };
	DeviceContext->ClearRenderTargetView(RenderTargetView, Color);
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
	SwapChain->Present(1, 0);
}

void GCPlatformRendererWin32D3D11::Shutdown()
{
	SAFE_RELEASE(RenderTargetView);
	SAFE_RELEASE(SwapChain);
	SAFE_RELEASE(DeviceContext);
	SAFE_RELEASE(Device);
}
