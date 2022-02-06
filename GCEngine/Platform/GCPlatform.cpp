#include "GCPlatform.h"
#include "../App/IGCApp.h"
#include "../Math/Vector2.h"

IGCPlatform::IGCPlatform()
	: Audio(nullptr)
	, Renderer(nullptr)
	, Input(nullptr)
	, FileIO(nullptr)
	, WindowWidth(0)
    , WindowHeight(0)
{
}

bool IGCPlatform::Initialize(IGCApp* App)
{
	bool IsInitializeSuccess = true;

	if (App)
	{
		IsInitializeSuccess &= InternalCreateWindow(App->ProgramName, App->WindowSize.X, App->WindowSize.Y);
	}

	IsInitializeSuccess &= InternalCreateRenderer();
	IsInitializeSuccess &= InternalCreateAudio();
	IsInitializeSuccess &= InternalCreateInput();
	IsInitializeSuccess &= InternalCreateFileIO();

	if (App)
	{
		IsInitializeSuccess &= App->Initialize(this);
	}

	_IsRunning = IsInitializeSuccess;
	return IsInitializeSuccess;
}

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

void IGCPlatform::Update(IGCApp* App)
{
	PreUpdate();

	if (App)
	{
		App->Update();
	}

	PostUpdate();
}


void IGCPlatform::Shutdown(IGCApp* App)
{
	if (App)
	{
		App->Shutdown();
	}

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
