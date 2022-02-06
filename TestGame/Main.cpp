#include "Platform/Win32/GCPlatformWin32.h"
#include "Game.h"

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowCode)
{
	Game MyGame;
	GCPlatformWin32 Win32Platform(Instance);
	{
		Win32Platform.Initialize(&MyGame);

		while (IGCPlatform::IsRunning())
		{
			Win32Platform.Update(&MyGame);
		}

		Win32Platform.Shutdown(&MyGame);
	}
	return 0;

}