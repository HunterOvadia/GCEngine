#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define SAFE_RELEASE(x) { if((x)) { (x)->Release(); (x) = nullptr; }}