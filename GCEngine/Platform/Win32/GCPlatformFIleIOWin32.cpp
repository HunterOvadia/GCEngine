#include "GCPlatformFileIOWin32.h"
#include "GCPlatformWin32.h"

IOFileResult GCPlatformFileIOWin32::ReadFile(const char* Filename)
{
	IOFileResult Result = { 0 };
	HANDLE FileHandle = CreateFileA(Filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if (FileHandle != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER FileSize;
		if (GetFileSizeEx(FileHandle, &FileSize))
		{
			int Size = FileSize.QuadPart;
			Result.SizeBytes = Size;
			Result.Content = VirtualAlloc(0, Size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			if (Result.Content)
			{
				DWORD ReadBytes;
				if (!::ReadFile(FileHandle, Result.Content, Result.SizeBytes, &ReadBytes, 0) && (Result.SizeBytes == ReadBytes))
				{
					VirtualFree(Result.Content, 0, MEM_RELEASE);
					Result.Content = nullptr;
				}
			}
		}
	}

	return Result;
}

bool GCPlatformFileIOWin32::WriteFile(const char* Filename, int Size, void* Content)
{
	bool Result = false;
	HANDLE FileHandle = CreateFileA(Filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	if (FileHandle != INVALID_HANDLE_VALUE)
	{
		DWORD WriteBytes;
		if (::WriteFile(FileHandle, Content, Size, &WriteBytes, 0))
		{
			Result = (WriteBytes == Size);
		}

		CloseHandle(FileHandle);
	}

	return Result;
}
