#include "GCPlatformAudioWin32.h"
#include "GCPlatformWin32.h"

GCPlatformAudioWin32::GCPlatformAudioWin32()
	: BufferSize(0)
	, DeviceEnumerator(nullptr)
	, Device(nullptr)
	, AudioClient(nullptr)
	, AudioRenderClient(nullptr)
	, IsInitialized(false)
{
}

bool GCPlatformAudioWin32::Initialize()
{
	HR_CHECK(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), reinterpret_cast<void**>(&DeviceEnumerator)));
	HR_CHECK(DeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &Device));
	HR_CHECK(Device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, reinterpret_cast<void**>(&AudioClient)));

	WAVEFORMATEX WaveFormat = {};
	WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	WaveFormat.nChannels = 2;
	WaveFormat.nSamplesPerSec = 44100;
	WaveFormat.wBitsPerSample = 16;
	WaveFormat.nBlockAlign = (WaveFormat.nChannels * WaveFormat.wBitsPerSample) / 8;
	WaveFormat.nAvgBytesPerSec = (WaveFormat.nSamplesPerSec * WaveFormat.nBlockAlign);

	constexpr REFERENCE_TIME BufferDuration = 100000000; // 0.01s
	HR_CHECK(AudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_RATEADJUST | AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM | AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY, BufferDuration, 0, &WaveFormat, nullptr));
	HR_CHECK(AudioClient->GetService(__uuidof(IAudioRenderClient), reinterpret_cast<void**>(&AudioRenderClient)));
	HR_CHECK(AudioClient->GetBufferSize(&BufferSize));
	HR_CHECK(AudioClient->Start());

	IsInitialized = true;
	return IsInitialized;
}

void GCPlatformAudioWin32::Shutdown()
{
	if (IsInitialized)
	{
		if (AudioClient)
		{
			AudioClient->Stop();
		}
		
		SAFE_RELEASE(DeviceEnumerator);
		SAFE_RELEASE(Device);
		SAFE_RELEASE(AudioClient);
		SAFE_RELEASE(AudioRenderClient);
		IsInitialized = false;
	}
}
