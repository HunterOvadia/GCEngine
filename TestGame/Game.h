#pragma once
#include "App/IGCApp.h"

class Game : public IGCApp
{
public:
	using IGCApp::IGCApp;

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