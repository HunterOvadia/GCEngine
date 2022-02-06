#pragma once

class IGCPlatformAudio
{
public:
	virtual ~IGCPlatformAudio() = default;
	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;
};