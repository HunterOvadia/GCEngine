#pragma once
#include "GCPlatformFileIO.h"

class GCPlatformFileIOWin32 : public IGCPlatformFileIO
{
public:
	virtual IOFileResult ReadFile(const char* Filename) override;
	virtual bool WriteFile(const char* Filename, int Size, void* Content) override;
};