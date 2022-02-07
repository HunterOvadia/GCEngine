#pragma once
#include "../GCEngine.h"

static inline int CStringLength(const char* String)
{
	int Count = 0;
	while (*String++)
	{
		++Count;
	}

	return Count;
}

class GCENGINE_API String
{
public:
	String() = default;
	String(const char* InString);
	~String();

	void Empty();
	void Prepend(const String& ToPrepend);
	void Append(const String& ToAppend);

	inline const int GetLength() const { return Length; }
	operator bool() const { return Length > 0 && Data != nullptr; }
	operator char* () const { return (char*)Data; }
	operator const char* () const { return (const char*)Data; }
	char operator[](int Index) const { GC_ASSERT(Index <= Length); return Data[Index]; }

private:
	char* Data;
	int Length;
};