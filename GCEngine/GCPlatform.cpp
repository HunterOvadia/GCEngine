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
}
