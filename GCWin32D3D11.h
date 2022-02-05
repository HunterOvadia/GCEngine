#pragma once
#include <d3d11.h>
#include <dxgi1_2.h>
#include "GCPlatform.h"

struct gc_win32_d3d11
{
	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;
	ID3D11RenderTargetView* RenderTargetView;
	IDXGISwapChain1* SwapChain;
};

extern bool Win32InitD3D11(gc_win32_d3d11* D3D11, HWND WindowHandle, int32 Width, int32 Height);
extern void Win32ShutdownD3D11(gc_win32_d3d11* D3D11);