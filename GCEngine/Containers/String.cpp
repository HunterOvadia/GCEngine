#include "String.h"
#include "../Memory/GCMemory.h"

String::String(const char* InString)
{
	if (InString == nullptr)
	{
		InString = "";
	}

	Length = CStringLength(InString);
	Data = (char *)GCMemory::Allocate(Length + 1);
	GCMemory::Copy(Data, InString, Length + 1);
}

String::~String()
{
	Empty();
}

void String::Empty()
{
	GCMemory::SafeFree(Data);
	Length = 0;
}

void String::Prepend(const String& ToPrepend)
{

}

void String::Append(const String& ToAppend)
{

}
