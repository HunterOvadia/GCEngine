#pragma once
#include <stdio.h>
#include <iostream>

class Game
{
public:
	void Init() 
	{
		MyPlatform = IGCPlatform::Get();
	}

	void Update() 
	{
		
	}

	void Shutdown() 
	{
		MyPlatform = nullptr;
	}

private:
	IGCPlatform* MyPlatform;
};