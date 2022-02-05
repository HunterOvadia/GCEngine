#include "GCWin32Audio.h"
#include "GCWin32.h"

bool Win32InitWASAPI(gc_win32_audio* Audio)
{
	HR_CHECK(CoCreateInstance(__uuidof(MMDeviceEnumerator), 0, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&Audio->DeviceEnumerator));
	HR_CHECK(Audio->DeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &Audio->Device));
	HR_CHECK(Audio->Device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, 0, (void**)&Audio->AudioClient));

	WAVEFORMATEX WaveFormat = { 0 };
	WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	WaveFormat.nChannels = 2;
	WaveFormat.nSamplesPerSec = 44100;
	WaveFormat.wBitsPerSample = 16;
	WaveFormat.nBlockAlign = (WaveFormat.nChannels * WaveFormat.wBitsPerSample) / 8;
	WaveFormat.nAvgBytesPerSec = (WaveFormat.nSamplesPerSec * WaveFormat.nBlockAlign);

	REFERENCE_TIME BufferDuration = 100000000; // 0.01s

	HR_CHECK(Audio->AudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_RATEADJUST | AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM | AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY, BufferDuration, 0, &WaveFormat, 0));
	HR_CHECK(Audio->AudioClient->GetService(__uuidof(IAudioRenderClient), (void**)&Audio->AudioRenderClient));
	HR_CHECK(Audio->AudioClient->GetBufferSize(&Audio->BufferSize));
	HR_CHECK(Audio->AudioClient->Start());
	Audio->IsInitialized = true;

	return Audio->IsInitialized;
}

void Win32ShutdownWASAPI(gc_win32_audio* Audio)
{
	if (Audio->IsInitialized)
	{
		if (Audio->AudioClient)
		{
			Audio->AudioClient->Stop();
		}

		SAFE_RELEASE(Audio->DeviceEnumerator);
		SAFE_RELEASE(Audio->Device);
		SAFE_RELEASE(Audio->AudioClient);
		SAFE_RELEASE(Audio->AudioRenderClient);

		Audio->IsInitialized = false;
	}
}