#pragma once
#include "../GCPlatformInput.h"
#include "GCPlatformWin32.h"

class GCPlatformInputWin32 final : public IGCPlatformInput
{
public:
	explicit GCPlatformInputWin32(HWND InWindowHandle);
	void ProcessMouseInput() override;

private:
	HWND WindowHandle;
};