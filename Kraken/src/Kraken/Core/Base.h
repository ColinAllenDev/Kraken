/* Base.h - Contains core macros used by the engine. */
#pragma once

#if defined KE_PLATFORM_WINDOWS
	#define KE_DEBUG_BREAK { __debugbreak(); }
	#ifdef KE_BUILD_DLL
		#define KRAKEN_API __declspec(dllexport)
	#else 
		#define KRAKEN_API __declspec(dllimport)
	#endif
#elif defined KE_PLATFORM_LINUX
	#include <signal.h>
	#define KE_DEBUG_BREAK { raise(SIGTRAP); }
	#ifdef KE_BUILD_DLL
		#define KRAKEN_API __attribute__((visibility("default")))
	#else
		#define KRAKEN_API
	#endif
#else
	#error Unsupported Platform!
#endif

#ifdef KE_DEBUG
	#define KE_ENABLE_ASSERTS
#endif

#ifdef KE_ENABLE_ASSERTS
	#define KE_ASSERT(x, ...) { if(!(x)) {KE_ERROR("Assertion Failed: {0}", __VA_ARGS__); KE_DEBUG_BREAK; } }
	#define KE_CORE_ASSERT(x, ...) { if(!(x)) {KE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); KE_DEBUG_BREAK; } }
#else
	#define KE_ASSERT(x, ...)
	#define KE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define KE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)