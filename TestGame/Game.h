#pragma once
class Game
{
public:
	Game() : MyPlatform(nullptr) {}
	
	void Init(IGCPlatform* InPlatform) 
	{
		MyPlatform = InPlatform;
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