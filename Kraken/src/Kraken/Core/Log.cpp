/* Kraken::Log Implementation */
#include "krpch.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Kraken {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		// Log Pattern: TIMESTAMP LOGGER_NAME: LOG_MSG
		// See https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// Define colors/level for core and client logger
		s_CoreLogger = spdlog::stdout_color_mt("KRAKEN");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}