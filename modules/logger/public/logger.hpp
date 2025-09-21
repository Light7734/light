#pragma once

#include <format>
#include <print>

/** Severity of a log message. */
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

/** Simple console logger */
class Logger
{
public:
	void static show_imgui_window();

	template<typename... Args>
	void static log(LogLvl lvl, std::format_string<Args...> fmt, Args &&...args) noexcept
	{
		std::ignore = lvl;
		std::println(fmt, std::forward<Args>(args)...);
	}

	void static log(LogLvl lvl, const char *message) noexcept
	{
		std::ignore = lvl;
		std::println("{}", message);
	}


private:
	Logger() = default;
};

template<typename... Args>
void log_trc(std::format_string<Args...> fmt, Args &&...args) noexcept
{
	Logger::log(LogLvl::trace, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void log_dbg(std::format_string<Args...> fmt, Args &&...args) noexcept
{
	Logger::log(LogLvl::debug, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void log_inf(std::format_string<Args...> fmt, Args &&...args) noexcept
{
	Logger::log(LogLvl::info, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void log_wrn(std::format_string<Args...> fmt, Args &&...args) noexcept
{
	Logger::log(LogLvl::warn, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void log_err(std::format_string<Args...> fmt, Args &&...args) noexcept
{
	Logger::log(LogLvl::error, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void log_crt(std::format_string<Args...> fmt, Args &&...args) noexcept
{
	Logger::log(LogLvl::critical, fmt, std::forward<Args>(args)...);
}
