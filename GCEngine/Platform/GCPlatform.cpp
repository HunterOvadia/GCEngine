#include "GCPlatform.h"

void IGCPlatform::PreUpdate()
{
	ProcessMessages();

	if (Input)
	{
		Input->ProcessMouseInput();
	}
}

void IGCPlatform::PostUpdate()
{
	if (Renderer)
	{
		Renderer->Update();
	}
}

IGCPlatform::IGCPlatform()
	: Audio(nullptr)
	, Renderer(nullptr)
	, Input(nullptr)
	, FileIO(nullptr)
	, WindowWidth(0)
    , WindowHeight(0)
{
}

bool IGCPlatform::Initialize(const char* ProgramName, const int Width, const int Height)
{
	bool IsInitializeSuccess = true;

	IsInitializeSuccess &= InternalCreateWindow(ProgramName, Width, Height);
	IsInitializeSuccess &= InternalCreateRenderer();
	IsInitializeSuccess &= InternalCreateAudio();
	IsInitializeSuccess &= InternalCreateInput();
	IsInitializeSuccess &= InternalCreateFileIO();

	_IsRunning = IsInitializeSuccess;
	return IsInitializeSuccess;
}

void IGCPlatform::Shutdown()
{
	if (Audio)
	{
		Audio->Shutdown();
		delete Audio;
		Audio = nullptr;
	}

	if (Renderer)
	{
		Renderer->Shutdown();
		delete Renderer;
		Renderer = nullptr;
	}

	if (Input)
	{
		delete Input;
		Input = nullptr;
	}

	if (FileIO)
	{
		delete FileIO;
		FileIO = nullptr;
	}
}

bool IGCPlatform::InternalCreateRenderer()
{
	Renderer = AssignRenderer();
	if (Renderer)
	{
		return Renderer->Initialize(WindowWidth, WindowHeight);
	}

	return false;
}

bool IGCPlatform::InternalCreateAudio()
{
	Audio = AssignAudio();
	if (Audio)
	{
		return Audio->Initialize();
	}

	return false;
}

bool IGCPlatform::InternalCreateInput()
{
	Input = AssignInput();
	if (Input)
	{
		return true;
	}

	return false;
}

bool IGCPlatform::InternalCreateFileIO()
{
	FileIO = AssignFileIO();
	if (FileIO)
	{
		return true;
	}

	return false;
}
