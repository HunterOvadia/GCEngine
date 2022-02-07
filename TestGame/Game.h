#pragma once
#include "App/IGCApp.h"
#include "Containers/Array.h"

class Game : public IGCApp
{
public:
	using IGCApp::IGCApp;

	virtual bool Initialize(IGCPlatform* Platform) override
	{
		Array<int> Test;
		for (int i = 0; i < 10; ++i)
		{
			Test.Add(i);
		}

		return true;
	}

	virtual void Update() override
	{
		
	}

	virtual void Shutdown() override
	{

	}
};