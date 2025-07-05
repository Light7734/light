#pragma once
#ifndef LIGHT_LOGGER_H
	#define LIGHT_LOGGER_H

	#include <engine/base/base.hpp>
	#include <spdlog/spdlog.h>

	#define LT_LOG_FILE_LOCATION "Logs/logger.txt"

	#ifndef LIGHT_DIST
		#define lt_log(logLevel, ...)                 \
			SPDLOG_LOGGER_CALL(                       \
			    ::Light::logger::get_engine_logger(), \
			    spdlog::level::logLevel,              \
			    __VA_ARGS__                           \
			)
	#else
		#define lt_log(logLevel, ...)               \
			SPDLOG_LOGGER_CALL(                     \
			    ::Light::logger::get_file_logger(), \
			    spdlog::level::logLevel,            \
			    __VA_ARGS__                         \
			)
	#endif

namespace Light {

class logger
{
public:
	static Scope<logger> create();

	static inline Ref<spdlog::logger> get_engine_logger()
	{
		return s_context->m_engine_logger;
	}
	static inline Ref<spdlog::logger> get_file_logger()
	{
		return s_context->m_file_logger;
	}

	void log_debug_data();

private:
	static logger *s_context;

	Ref<spdlog::logger> m_engine_logger, m_file_logger;

	std::string m_log_file_path;

	logger();
};

} // namespace Light

#endif
