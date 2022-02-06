#pragma once
#include "GCPlatformInput.h"
#include "GCPlatformWin32.h"

class GCPlatformInputWin32 : public IGCPlatformInput
{
public:
	GCPlatformInputWin32(HWND InWindowHandle);
	virtual void ProcessMouseInput() override;

private:
	HWND WindowHandle;
};