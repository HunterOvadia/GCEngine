#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define SAFE_RELEASE(x) { if((x)) { (x)->Release(); (x) = nullptr; }}

// TODO(HO): More Details
#define HR_CHECK(Exp) { if(!(SUCCEEDED(Exp))) { MessageBoxA(0, "Fatal Error", "Fatal Error", MB_OK); } }