#pragma once

class IGCPlatformRenderer
{
public:
	virtual bool Initialize(int Width, int Height) = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;
};