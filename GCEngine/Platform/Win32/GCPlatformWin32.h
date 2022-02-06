#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "../GCPlatform.h"

inline LPSTR Win32GetLastError()
{
	LPSTR MessageBuffer = nullptr;
	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, GetLastError(), 0, (LPSTR)&MessageBuffer, 0, nullptr);
	return MessageBuffer;
}

#define SAFE_RELEASE(x) { if((x)) { (x)->Release(); (x) = nullptr; }}
#define HR_CHECK(Exp) { if(!(SUCCEEDED(Exp))) { MessageBoxA(0, Win32GetLastError(), "Fatal Error", MB_OK); } }


class GCENGINE_API GCPlatformWin32 final : public IGCPlatform
{
public:
	explicit GCPlatformWin32(HINSTANCE InInstance);
	void ProcessMessages() override;

private:
	IGCPlatformRenderer* AssignRenderer() override;
	IGCPlatformInput* AssignInput() override;
	IGCPlatformFileIO* AssignFileIO() override;
	IGCPlatformAudio* AssignAudio() override;
	bool InternalCreateWindow(const char* ProgramName, int Width, int Height) override;

private:
	static LRESULT Win32WindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);

private:
	HINSTANCE Instance;
	HWND WindowHandle;
};