#pragma once

#include <cstdint>

typedef int64_t i64;
typedef uint64_t u64;
typedef uint64_t b64;

typedef int32_t i32;
typedef uint32_t u32;
typedef uint32_t b32;

typedef int16_t i16;
typedef uint16_t u16;
typedef uint16_t b16;

typedef int8_t i8;
typedef uint8_t u8;
typedef uint8_t b8;

typedef float f32;
typedef double f64;

#define KAPI

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#	define KPLATFORM_WINDOWS 1
#	ifndef _WIN64
#		error "64-bit is required on Windows!"
#	endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#	define KPLATFORM_LINUX 1
#	if defined(__ANDROID__)
#		define KPLATFORM_ANDROID 1
#	endif
#elif defined(__unix__)
// Catch anything not caught by the above.
#	define KPLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
// Posix
#	define KPLATFORM_POSIX 1
#elif __APPLE__
// Apple platforms
#	define KPLATFORM_APPLE 1
#	include <TargetConditionals.h>
#	if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#		define KPLATFORM_IOS 1
#		define KPLATFORM_IOS_SIMULATOR 1
#	elif TARGET_OS_IPHONE
#		define KPLATFORM_IOS 1
// iOS device
#	elif TARGET_OS_MAC
// HACK: Should probably be in the Vulkan Renderer lib, not here.
#		define VK_USE_PLATFORM_MACOS_MVK
// Other kinds of Mac OS
#	else
#		error "Unknown Apple platform"
#	endif
#else
#	error "Unknown platform!"
#endif

//#ifdef KAPI_EXPORT
//#define KAPI __declspec(dllexport)
//#else
//#define KAPI __declspec(dllimport)
//#endif
