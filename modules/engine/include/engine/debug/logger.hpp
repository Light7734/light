#pragma once

#include <any>
#include <format>
#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

/** @brief Severity of a log message.
 *
 * @note Values reflect spdlog::lvl
 */
enum class LogLvl : uint8_t
{
	/** Lowest and most vebose log level, for tracing execution paths and events */
	trace = 0,

	/** Vebose log level, for enabling temporarily to debug */
	debug = 1,

	/** General information */
	info = 2,

	/** Things we should to be aware of and edge cases */
	warn = 3,

	/** Defects, bugs and undesired behaviour */
	error = 4,

	/** Unrecoverable errors */
	critical = 5,

	/** No logging */
	off = 6,
};

namespace spdlog {
class logger;
}

/** Responsible for logging */
class Logger
{
public:
	void static show_imgui_window();

	template<typename... Args>
	void static log(LogLvl lvl, std::format_string<Args...> fmt, Args &&...args)
	{
		instance().spd_logger->log(
		    (spdlog::level::level_enum)lvl,
		    std::format(fmt, std::forward<Args>(args)...)
		);
	}

private:
	Logger();

	~Logger();

	auto static instance() -> Logger &;

	std::shared_ptr<spdlog::logger> spd_logger;
};

template<typename... Args>
void log_trc(std::format_string<Args...> fmt, Args &&...args)
{
	Logger::log(LogLvl::trace, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void log_dbg(std::format_string<Args...> fmt, Args &&...args)
{
	Logger::log(LogLvl::debug, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void log_inf(std::format_string<Args...> fmt, Args &&...args)
{
	Logger::log(LogLvl::info, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void log_wrn(std::format_string<Args...> fmt, Args &&...args)
{
	Logger::log(LogLvl::warn, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void log_err(std::format_string<Args...> fmt, Args &&...args)
{
	Logger::log(LogLvl::error, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void log_crt(std::format_string<Args...> fmt, Args &&...args)
{
	Logger::log(LogLvl::critical, fmt, std::forward<Args>(args)...);
}
