#include "GCPlatformWin32.h"


int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowCode)
{
	GCPlatformWin32 Win32Platform(Instance);

	Win32Platform.Initialize();
	while (IGCPlatform::IsRunning())
	{
		Win32Platform.Run();
	}
	Win32Platform.Shutdown();

	return 0;
}