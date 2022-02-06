#pragma once

#include "GCPlatformAudio.h"
#include "GCPlatformRenderer.h"
#include "GCPlatformInput.h"
#include "GCPlatformFileIO.h"
#include "GCEngine.h"

#define WINDOW_TITLE "GCEngine"
#define WINDOW_DEFAULT_WIDTH 1280
#define WINDOW_DEFAULT_HEIGHT 720
#define ARRAY_SIZE(Array) ((sizeof(Array)/sizeof(Array[0])))

class GCENGINE_API IGCPlatform
{
public:
	virtual bool Initialize() = 0;
	virtual void ProcessMessages() = 0;

	virtual void PreUpdate();
	virtual void PostUpdate();

	virtual void Shutdown();

	IGCPlatformAudio* GetAudio() { return Audio; }
	IGCPlatformRenderer* GetRenderer() { return Renderer; }
	IGCPlatformInput* GetInput() { return Input;  }
	IGCPlatformFileIO* GetFileIO() { return FileIO; }

	static bool IsRunning() { return _IsRunning; }
	static IGCPlatform* Get() { return GlobalPlatform; }

protected:
	static void SetPlatform(IGCPlatform* InPlatform) { GlobalPlatform = InPlatform; }

private:
	static IGCPlatform* GlobalPlatform;

protected:
	IGCPlatformAudio* Audio;
	IGCPlatformRenderer* Renderer;
	IGCPlatformInput* Input;
	IGCPlatformFileIO* FileIO;

	int WindowWidth;
	int WindowHeight;
	static bool _IsRunning;
};

