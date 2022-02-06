#pragma once

struct IOFileResult
{
	void* Content;
	int SizeBytes;
};

class IGCPlatformFileIO
{
public:
	virtual ~IGCPlatformFileIO() = default;
	virtual IOFileResult ReadFile(const char* Filename) = 0;
	virtual bool WriteFile(const char* Filename, int Size, void* Content) = 0;
};