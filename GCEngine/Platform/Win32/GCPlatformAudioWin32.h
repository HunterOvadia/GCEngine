#pragma once
#include "GCPlatformAudio.h"
#include <mmdeviceapi.h>
#include <Audioclient.h>

class GCPlatformAudioWin32 : public IGCPlatformAudio
{
public:
	virtual bool Initialize() override;
	virtual void Shutdown() override;

private:
	UINT32 BufferSize;
	IMMDeviceEnumerator* DeviceEnumerator;
	IMMDevice* Device;
	IAudioClient* AudioClient;
	IAudioRenderClient* AudioRenderClient;
	bool IsInitialized;
};