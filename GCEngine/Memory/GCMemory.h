#pragma once

#if _WIN32
#include <Windows.h>
#else
#include <memory>
#endif

class GCMemory
{
public:
	static void* Allocate(size_t Size)
	{
#if _WIN32
		return VirtualAlloc(0, Size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
		return malloc(Size);
#endif
	}

	static void* ReAllocate(void* Memory, size_t Size)
	{
#if _WIN32
		return HeapReAlloc(0, 0, Memory, Size);
#else
		return realloc(Memory, Size);
#endif
	}

	static void Free(void* Memory)
	{
#if _WIN32
		VirtualFree(Memory, 0, MEM_RELEASE);
#else
		free(Memory);
#endif			
	}

	static void SafeFree(void* Memory)
	{
		if (Memory)
		{
			Free(Memory);
			Memory = nullptr;
		}
	}

	static void* Copy(void* Destination, const void* Source, size_t Size)
	{
		char* Dest = (char *)Destination;
		const char* Src = (char *)Source;

		// NOTE(HO): If they are the same address, don't copy.
		if (Dest == Src)
		{
			return Dest;
		}

		while (Size--)
		{
			*Dest++ = *Src++;
		}

		return Dest;
	}

	static void* Move(void* Destination, const void* Source, size_t Size)
	{
		char* Dest = (char*)Destination;
		const char* Src = (char*)Source;

		// NOTE(HO): If they are the same address, don't move.
		if (Dest == Src)
		{
			return Dest;
		}
		// NOTE(HO): If they overlap, copy from the end
		else if (Src < Dest && Dest < (Src + Size))
		{
			Src += Size;
			Dest += Size;
			while (Size--)
			{
				*Dest-- = *Src--;
			}
		}
		else
		{
			Copy(Dest, Source, Size);
		}

		return Dest;
	}
};