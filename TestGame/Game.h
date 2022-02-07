#pragma once
#include "App/IGCApp.h"
#include "Containers/String.h"

class Game : public IGCApp
{
public:
	using IGCApp::IGCApp;

	virtual bool Initialize(IGCPlatform* Platform) override
	{
		String Test = "Hello!";
		String Test2 = "Wazzup!";

		Test.Append(Test2);

		return true;
	}

	virtual void Update() override
	{
		
	}

	virtual void Shutdown() override
	{

	}
};