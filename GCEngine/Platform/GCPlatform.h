#pragma once

#include "GCPlatformAudio.h"
#include "GCPlatformRenderer.h"
#include "GCPlatformInput.h"
#include "GCPlatformFileIO.h"
#include "GCEngine.h"

#define ARRAY_SIZE(Array) ((sizeof(Array)/sizeof(Array[0])))

class GCENGINE_API IGCPlatform
{
public:
	virtual bool Initialize(const char* ProgramName, int Width, int Height);
	virtual void ProcessMessages() = 0;
	virtual void Shutdown();

	// TODO(HO): Can we just make these private?
	virtual void PreUpdate();
	virtual void PostUpdate();

	IGCPlatformAudio* GetAudio() { return Audio; }
	IGCPlatformRenderer* GetRenderer() { return Renderer; }
	IGCPlatformInput* GetInput() { return Input;  }
	IGCPlatformFileIO* GetFileIO() { return FileIO; }

	static bool IsRunning() { return _IsRunning; }

private:
	virtual bool InternalCreateWindow(const char* ProgramName, int Width, int Height) = 0;
	virtual IGCPlatformRenderer* AssignRenderer() = 0;
	virtual IGCPlatformInput* AssignInput() = 0;
	virtual IGCPlatformFileIO* AssignFileIO() = 0;
	virtual IGCPlatformAudio* AssignAudio() = 0;

	bool InternalCreateRenderer();
	bool InternalCreateAudio();
	bool InternalCreateInput();
	bool InternalCreateFileIO();

protected:
	IGCPlatformAudio* Audio;
	IGCPlatformRenderer* Renderer;
	IGCPlatformInput* Input;
	IGCPlatformFileIO* FileIO;

	int WindowWidth;
	int WindowHeight;
	static bool _IsRunning;
};

