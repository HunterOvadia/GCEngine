#pragma once
#include "../GCPlatformAudio.h"
#include <mmdeviceapi.h>
#include <Audioclient.h>

class GCPlatformAudioWin32 final : public IGCPlatformAudio
{
public:
	GCPlatformAudioWin32();
	bool Initialize() override;
	void Shutdown() override;

private:
	UINT32 BufferSize;
	IMMDeviceEnumerator* DeviceEnumerator;
	IMMDevice* Device;
	IAudioClient* AudioClient;
	IAudioRenderClient* AudioRenderClient;
	bool IsInitialized;
};