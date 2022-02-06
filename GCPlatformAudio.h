#pragma once

class IGCPlatformAudio
{
public:
	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;
};