/** Kraken::Log - Logging class. Defines loggers for Core and Client as well as expose logging macros using spdlog library. **/

#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Kraken {
	class KRAKEN_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// MACROS: Core Logging
#define KR_CORE_TRACE(...)::Kraken::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KR_CORE_INFO(...)::Kraken::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KR_CORE_WARN(...)::Kraken::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KR_CORE_ERROR(...)::Kraken::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KR_CORE_FATAL(...)::Kraken::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// MACROS: Client Logging
#define KR_TRACE(...)::Kraken::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KR_INFO(...)::Kraken::Log::GetClientLogger()->info(__VA_ARGS__)
#define KR_WARN(...)::Kraken::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KR_ERROR(...)::Kraken::Log::GetClientLogger()->error(__VA_ARGS__)
#define KR_FATAL(...)::Kraken::Log::GetClientLogger()->fatal(__VA_ARGS__)
