#include "GCPlatformWin32.h"
#include "GCPlatformAudioWin32.h"
#include "GCPlatformRendererWin32D3D11.h"

bool IGCPlatform::_IsRunning = false;

GCPlatformWin32::GCPlatformWin32(HINSTANCE InInstance) 
	: Instance(InInstance)
	, WindowHandle(nullptr)
{
}

bool GCPlatformWin32::Initialize()
{
	bool CanRun = true;

	CanRun &= MakeWindow();

	Audio = new GCPlatformAudioWin32();
	if (Audio)
	{
		CanRun &= Audio->Initialize();
	}

	Renderer = new GCPlatformRendererWin32D3D11(WindowHandle);
	if (Renderer)
	{
		CanRun &= Renderer->Initialize(WindowWidth, WindowHeight);
	}

	if (CanRun)
	{
		_IsRunning = true;
	}

	return _IsRunning;
}

void GCPlatformWin32::Run()
{
	MSG Message;
	while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	if (Renderer)
	{
		Renderer->Update();
	}
}

void GCPlatformWin32::Shutdown()
{
	if (Audio)
	{
		Audio->Shutdown();
	}

	if (Renderer)
	{
		Renderer->Shutdown();
	}
}

bool GCPlatformWin32::MakeWindow()
{
	WNDCLASSA WindowClass = { 0 };

	WindowClass.lpfnWndProc = Win32WindowCallback;
	WindowClass.hInstance = Instance;
	WindowClass.hCursor = LoadCursor(0, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	WindowClass.lpszClassName = "GCWindowClass";

	if (RegisterClassA(&WindowClass))
	{
		DWORD WindowStyles = WS_OVERLAPPEDWINDOW;
		RECT WindowRect = { 0 };
		WindowRect.right = WINDOW_DEFAULT_WIDTH;
		WindowRect.bottom = WINDOW_DEFAULT_HEIGHT;
		AdjustWindowRect(&WindowRect, WindowStyles, 0);

		WindowWidth = (WindowRect.right - WindowRect.left);
		WindowHeight = (WindowRect.bottom - WindowRect.top);
		int WindowCenterX = ((GetSystemMetrics(SM_CXSCREEN) - WindowWidth) / 2);
		int WindowCenterY = ((GetSystemMetrics(SM_CYSCREEN) - WindowHeight) / 2);

		WindowHandle = CreateWindowExA(0, WindowClass.lpszClassName, WINDOW_TITLE, WindowStyles, WindowCenterX, WindowCenterY, WindowWidth, WindowHeight, NULL, NULL, Instance, NULL);
		if (WindowHandle)
		{
			ShowWindow(WindowHandle, 1);
			return true;
		}

		return false;
	}
}

LRESULT GCPlatformWin32::Win32WindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	LRESULT Result = 0;
	switch (Message)
	{
		case WM_DESTROY:
		case WM_CLOSE:
		{
			_IsRunning = false;
			break;
		}
		default:
		{
			Result = DefWindowProcA(Window, Message, WParam, LParam);
			break;
		}
	}
	return Result;
}