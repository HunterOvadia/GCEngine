#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "GCPlatform.h"

static bool GlobalRunning = false;

static LRESULT Win32WindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	LRESULT Result = 0;
	switch (Message)
	{
		case WM_DESTROY:
		case WM_CLOSE:
		{
			GlobalRunning = false;
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

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowCode)
{
	UNUSED_ARG(CommandLine);
	UNUSED_ARG(ShowCode);
	UNUSED_ARG(PrevInstance);

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

		int32 WindowWidth = (WindowRect.right - WindowRect.left);
		int32 WindowHeight = (WindowRect.bottom - WindowRect.top);
		int32 WindowCenterX = ((GetSystemMetrics(SM_CXSCREEN) - WindowWidth) / 2);
		int32 WindowCenterY = ((GetSystemMetrics(SM_CYSCREEN) - WindowHeight) / 2);

		HWND Window = CreateWindowExA(0, WindowClass.lpszClassName, WINDOW_TITLE, WindowStyles, WindowCenterX, WindowCenterY, WindowWidth, WindowHeight, NULL, NULL, Instance, NULL);
		if (Window)
		{
			ShowWindow(Window, ShowCode);

			GlobalRunning = true;
			while (GlobalRunning)
			{
				MSG Message;
				while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
			}
		}
	}

	return 0;
}