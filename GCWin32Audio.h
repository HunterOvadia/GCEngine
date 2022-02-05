#pragma once
#include <mmdeviceapi.h>
#include <Audioclient.h>
#include "GCPlatform.h"

struct gc_win32_audio
{
	bool IsInitialized;

	uint32 BufferSize;
	IMMDeviceEnumerator* DeviceEnumerator;
	IMMDevice* Device;
	IAudioClient* AudioClient;
	IAudioRenderClient* AudioRenderClient;
};

extern bool Win32InitWASAPI(gc_win32_audio* Audio);
extern void Win32ShutdownWASAPI(gc_win32_audio* Audio);