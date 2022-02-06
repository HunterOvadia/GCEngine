#include "GCPlatformInputWin32.h"

GCPlatformInputWin32::GCPlatformInputWin32(HWND InWindowHandle)
	: WindowHandle(InWindowHandle)
{
}

void GCPlatformInputWin32::ProcessMouseInput()
{
	POINT MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(WindowHandle, &MousePoint);
	MouseX = MousePoint.x;
	MouseY = MousePoint.y;
}
