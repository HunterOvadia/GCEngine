#pragma once
#include "../GCPlatformFileIO.h"

class GCPlatformFileIOWin32 final : public IGCPlatformFileIO
{
public:
	IOFileResult ReadFile(const char* Filename) override;
	bool WriteFile(const char* Filename, int Size, void* Content) override;
};