#pragma once
#include <stdio.h>
#include <iostream>

class Game
{
public:
	void Init(IGCPlatform* InPlatforn) 
	{
		MyPlatform = InPlatforn;
	}

	void Update() 
	{
				
	}

	void Shutdown() 
	{
	}

private:
	IGCPlatform* MyPlatform;
};