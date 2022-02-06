#pragma once
#include "GCPlatformAudio.h"
#include "GCPlatformRenderer.h"
#include "GCPlatformInput.h"
#include "GCPlatformFileIO.h"

#define WINDOW_TITLE "GCEngine"
#define WINDOW_DEFAULT_WIDTH 1280
#define WINDOW_DEFAULT_HEIGHT 720
#define ARRAY_SIZE(Array) ((sizeof(Array)/sizeof(Array[0])))
class IGCPlatform
{
public:
	virtual bool Initialize() = 0;
	virtual void ProcessMessages() = 0;

	virtual void Run();
	virtual void Shutdown();
	static bool IsRunning() { return _IsRunning; }

protected:
	IGCPlatformAudio* Audio;
	IGCPlatformRenderer* Renderer;
	IGCPlatformInput* Input;
	IGCPlatformFileIO* FileIO;

	int WindowWidth;
	int WindowHeight;

	static bool _IsRunning;
};

