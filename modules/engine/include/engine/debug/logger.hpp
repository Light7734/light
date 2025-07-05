#pragma once
#ifndef LIGHT_LOGGER_H
	#define LIGHT_LOGGER_H

	#include <engine/base/base.hpp>
	#include <spdlog/spdlog.h>

	#define LT_LOG_FILE_LOCATION "Logs/Logger.txt"

	#ifndef LIGHT_DIST
		#define LOG(logLevel, ...)                  \
			SPDLOG_LOGGER_CALL(                     \
			    ::Light::Logger::GetEngineLogger(), \
			    spdlog::level::logLevel,            \
			    __VA_ARGS__                         \
			)
	#else
		#define LOG(logLevel, ...)                \
			SPDLOG_LOGGER_CALL(                   \
			    ::Light::Logger::GetFileLogger(), \
			    spdlog::level::logLevel,          \
			    __VA_ARGS__                       \
			)
	#endif

namespace Light {

// #todo: extend
class Logger /* singleton */
{
private:
	static Logger *s_Context;

private:
	Ref<spdlog::logger> m_engine_logger, m_file_logger;
	std::string m_log_file_path;

public:
	static Scope<Logger> Create();

	static inline Ref<spdlog::logger> GetEngineLogger()
	{
		return s_Context->m_engine_logger;
	}
	static inline Ref<spdlog::logger> GetFileLogger()
	{
		return s_Context->m_file_logger;
	}

	void LogDebugData();

private:
	Logger();
};

} // namespace Light

#endif
