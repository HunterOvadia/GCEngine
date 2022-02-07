#pragma once

#include "GCPlatformAudio.h"
#include "GCPlatformRenderer.h"
#include "GCPlatformInput.h"
#include "GCPlatformFileIO.h"
#include "../GCEngine.h"

class IGCApp;

class GCENGINE_API IGCPlatform
{
public:
	IGCPlatform();
	virtual ~IGCPlatform() = default;
	virtual void ProcessMessages() = 0;

	virtual bool Initialize(IGCApp* App);
	virtual void Update(IGCApp* App);
	virtual void Shutdown(IGCApp* App);

	IGCPlatformAudio* GetAudio() const { return Audio; }
	IGCPlatformRenderer* GetRenderer() const { return Renderer; }
	IGCPlatformInput* GetInput() const { return Input;  }
	IGCPlatformFileIO* GetFileIO() const { return FileIO; }

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

	virtual void PreUpdate();
	virtual void PostUpdate();

protected:
	IGCPlatformAudio* Audio;
	IGCPlatformRenderer* Renderer;
	IGCPlatformInput* Input;
	IGCPlatformFileIO* FileIO;

	int WindowWidth;
	int WindowHeight;
	static bool _IsRunning;
};