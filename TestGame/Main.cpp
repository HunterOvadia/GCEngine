#include "GCPlatformWin32.h"
#include "Game.h"

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowCode)
{
	GCPlatformWin32 Win32Platform(Instance);
	Win32Platform.Initialize();
	
	Game MyGame;
	MyGame.Init();

	while (IGCPlatform::IsRunning())
	{
		Win32Platform.PreUpdate();
		MyGame.Update();
		Win32Platform.PostUpdate();
	}

	MyGame.Shutdown();
	Win32Platform.Shutdown();
	return 0;
}