#include "GCPlatform.h"

void IGCPlatform::Run()
{
	ProcessMessages();

	if (Input)
	{
		Input->ProcessMouseInput();
	}

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
