#pragma once

#ifdef GCENGINE_EXPORT
	#define GCENGINE_API __declspec(dllexport)
#else
	#define GCENGINE_API __declspec(dllimport)
#endif

#define ARRAY_SIZE(Array) ((sizeof(Array)/sizeof(Array[0])))

#ifdef GC_DEBUG
	#define GC_ASSERT(Expression) if(!(Expression)) { *(volatile int *)0 = 0; }
#else
	#define GC_ASSERT(Expression) (Expression);
#endif