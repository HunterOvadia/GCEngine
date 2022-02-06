#pragma once
#include "App/IGCApp.h"

class Game : public IGCApp
{
public:
	Game() : IGCApp("MyGame", 1280, 720) {}

	virtual bool Initialize(IGCPlatform* Platform) override
	{
		return true;
	}

	virtual void Update() override
	{
		
	}

	virtual void Shutdown() override
	{

	}
};