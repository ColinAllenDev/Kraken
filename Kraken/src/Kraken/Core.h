/* Core.h - Contains core macros used by the engine. */
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

#define BIT(x) (1 << x)