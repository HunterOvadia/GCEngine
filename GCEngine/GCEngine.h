#pragma once

#ifdef GCENGINE_EXPORT
	#define GCENGINE_API __declspec(dllexport)
#else
	#define GCENGINE_API __declspec(dllimport)
#endif