#if !defined(GC_PLATFORM_H)
#include <stdint.h>

#define WINDOW_TITLE "GCEngine"
#define WINDOW_DEFAULT_WIDTH 1280
#define WINDOW_DEFAULT_HEIGHT 720

typedef int8_t		int8;
typedef int16_t		int16;
typedef int32_t		int32;
typedef int64_t		int64;

typedef uint8_t		uint8;
typedef uint16_t	uint16;
typedef uint32_t	uint32;
typedef uint64_t	uint64;

#define ASSERT(Expression) if(!(Expression)) { *(int *)0 = 0; }
#define ARRAY_SIZE(Array) (sizeof(Array) / sizeof((Array)[0]))

#define KILOBYTES(N) ((N) * 1024)
#define MEGABYTES(N) (KILOBYTES(N) * 1024)
#define GIGABYTES(N) (MEGABYTES(N) * 1024)
#define UNUSED_ARG(X) (X)

#define GC_PLATFORM_H
#endif