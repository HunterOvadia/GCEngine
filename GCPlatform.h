#pragma once
#include "GCPlatformAudio.h"
#include "GCPlatformRenderer.h"

#define WINDOW_TITLE "GCEngine"
#define WINDOW_DEFAULT_WIDTH 1280
#define WINDOW_DEFAULT_HEIGHT 720
#define ARRAY_SIZE(Array) ((sizeof(Array)/sizeof(Array[0])))
class IGCPlatform
{
public:
	virtual bool Initialize() = 0;
	virtual void Run() = 0;
	virtual void Shutdown() = 0;
	static bool IsRunning() { return _IsRunning; }

protected:
	IGCPlatformAudio* Audio;
	IGCPlatformRenderer* Renderer;

	int WindowWidth;
	int WindowHeight;

	static bool _IsRunning;
};