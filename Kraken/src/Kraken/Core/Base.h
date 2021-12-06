/* Base.h - Contains core macros used by the engine. */
#pragma once

#ifdef KR_PLATFORM_WINDOWS
	#ifdef KR_BUILD_DLL
		#define KRAKEN_API __declspec(dllexport)
	#else 
		#define KRAKEN_API __declspec(dllimport)
	#endif
#else
	#error Kraken only supports Windows!
#endif

#ifdef KR_ENABLE_ASSERTS
	#define KR_ASSERT(x, ...) { if(!(x)) {KR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define KR_CORE_ASSERT(x, ...) { if(!(x)) {KR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define KR_ASSERT(x, ...)
	#define KR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)