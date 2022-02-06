#include "GCPlatformFileIOWin32.h"
#include "GCPlatformWin32.h"

IOFileResult GCPlatformFileIOWin32::ReadFile(const char* Filename)
{
	IOFileResult Result = {};
	const HANDLE FileHandle = CreateFileA(Filename, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	if (FileHandle != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER FileSize;
		if (GetFileSizeEx(FileHandle, &FileSize))
		{
			const int Size = FileSize.QuadPart;
			Result.SizeBytes = Size;
			Result.Content = VirtualAlloc(nullptr, Size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			if (Result.Content)
			{
				DWORD ReadBytes;
				if (!::ReadFile(FileHandle, Result.Content, Result.SizeBytes, &ReadBytes, nullptr) && (Result.SizeBytes == ReadBytes))
				{
					VirtualFree(Result.Content, 0, MEM_RELEASE);
					Result.Content = nullptr;
				}
			}
		}
	}

	return Result;
}

bool GCPlatformFileIOWin32::WriteFile(const char* Filename, const int Size, void* Content)
{
	bool Result = false;
	const HANDLE FileHandle = CreateFileA(Filename, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
	if (FileHandle != INVALID_HANDLE_VALUE)
	{
		DWORD WriteBytes;
		if (::WriteFile(FileHandle, Content, Size, &WriteBytes, nullptr))
		{
			Result = (WriteBytes == Size);
		}

		CloseHandle(FileHandle);
	}

	return Result;
}
