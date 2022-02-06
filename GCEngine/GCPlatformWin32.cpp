#include "GCPlatformWin32.h"
#include "GCPlatformAudioWin32.h"
#include "GCPlatformRendererWin32D3D11.h"
#include "GCPlatformInputWin32.h"
#include "GCPlatformFileIOWin32.h"

bool IGCPlatform::_IsRunning = false;
GCPlatformWin32::GCPlatformWin32(HINSTANCE InInstance) 
	: Instance(InInstance)
	, WindowHandle(nullptr)
{
}

IGCPlatformRenderer* GCPlatformWin32::AssignRenderer()
{
	return new GCPlatformRendererWin32D3D11(WindowHandle);
}

IGCPlatformInput* GCPlatformWin32::AssignInput()
{
	return new GCPlatformInputWin32(WindowHandle);
}

IGCPlatformFileIO* GCPlatformWin32::AssignFileIO()
{
	return new GCPlatformFileIOWin32();
}

IGCPlatformAudio* GCPlatformWin32::AssignAudio()
{
	return new GCPlatformAudioWin32();
}

bool GCPlatformWin32::InternalCreateWindow(const char* ProgramName, int Width, int Height)
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
		WindowRect.right = Width;
		WindowRect.bottom = Height;
		AdjustWindowRect(&WindowRect, WindowStyles, 0);

		WindowWidth = (WindowRect.right - WindowRect.left);
		WindowHeight = (WindowRect.bottom - WindowRect.top);
		int WindowCenterX = ((GetSystemMetrics(SM_CXSCREEN) - WindowWidth) / 2);
		int WindowCenterY = ((GetSystemMetrics(SM_CYSCREEN) - WindowHeight) / 2);

		WindowHandle = CreateWindowExA(0, WindowClass.lpszClassName, ProgramName, WindowStyles, WindowCenterX, WindowCenterY, WindowWidth, WindowHeight, NULL, NULL, Instance, NULL);
		if (WindowHandle)
		{
			ShowWindow(WindowHandle, 1);
			return true;
		}
	}

	return false;
}

void GCPlatformWin32::ProcessMessages()
{
	MSG Message;
	while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
	{
		switch (Message.message)
		{
			default:
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
				break;
			}
		}
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