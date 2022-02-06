#include "Platform/Win32/GCPlatformWin32.h"
#include "Game.h"

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowCode)
{
	GCPlatformWin32 Win32Platform(Instance);
	Win32Platform.Initialize("MyGame", 1280, 720);
	
	Game MyGame = {};
	MyGame.Init(&Win32Platform);

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