#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "GCPlatform.h"

#define SAFE_RELEASE(x) { if((x)) { (x)->Release(); (x) = nullptr; }}
// TODO(HO): More Details
#define HR_CHECK(Exp) { if(!(SUCCEEDED(Exp))) { MessageBoxA(0, "Fatal Error", "Fatal Error", MB_OK); } }


class GCENGINE_API GCPlatformWin32 : public IGCPlatform
{
public:
	GCPlatformWin32(HINSTANCE InInstance);
	virtual bool Initialize() override;
	virtual void ProcessMessages();

private:
	bool MakeWindow();
	static LRESULT Win32WindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);

private:
	HINSTANCE Instance;
	HWND WindowHandle;
};