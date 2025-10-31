#pragma once

#include <cstdint>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <source_location>
#include <string_view>
#include <thread>
#include <utility>

namespace lt::log {

/** Severity of a log message. */
enum class Level : uint8_t
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

namespace details {

inline auto thread_hash_id() noexcept -> std::uint64_t
{
	return static_cast<std::uint64_t>(std::hash<std::thread::id> {}(std::this_thread::get_id()));
}

} // namespace details

template<typename... Args>
struct [[maybe_unused]] print
{
	[[maybe_unused]] print(
	    Level level,
	    const std::source_location &location,
	    std::format_string<Args...> format,
	    Args &&...arguments
	) noexcept
	{
		constexpr auto to_string = [](Level level, auto location) {
			// clang-format off
			switch (level)
			{
			using enum Level;
			case trace   : return "\033[1;37m| trc |\033[0m";
			case debug   : return "\033[1;36m| dbg |\033[0m";
			case info    : return "\033[1;32m| inf |\033[0m";
			case warn    : return "\033[1;33m| wrn |\033[0m";
			case error   : return "\033[1;31m| err |\033[0m";
			case critical: return "\033[1;41m| crt |\033[0m";
			case off: return "off";
			}
			// clang-format on

			std::unreachable();
		};

		const auto path = std::filesystem::path { location.file_name() };

		std::println(
		    "{} {} ==> {}",
		    to_string(level, location),
		    std::format("{}:{}", path.filename().c_str(), location.line()),
		    std::format(format, std::forward<Args &&>(arguments)...)
		);
	}
};

template<typename... Args>
print(Level level, std::format_string<Args...>, Args &&...) noexcept -> print<Args...>;

template<typename... Args>
struct [[maybe_unused]] trace
{
	[[maybe_unused]] trace(
	    std::format_string<Args...> format,
	    Args &&...arguments,
	    const std::source_location &location = std::source_location::current()
	) noexcept
	{
		print(Level::trace, location, format, std::forward<Args &&>(arguments)...);
	}
};

template<typename... Args>
trace(std::format_string<Args...>, Args &&...) noexcept -> trace<Args...>;

template<typename... Args>
struct [[maybe_unused]] debug
{
	[[maybe_unused]] debug(
	    std::format_string<Args...> format,
	    Args &&...arguments,
	    const std::source_location &location = std::source_location::current()
	) noexcept
	{
		print(Level::debug, location, format, std::forward<Args &&>(arguments)...);
	}
};

template<typename... Args>
debug(std::format_string<Args...>, Args &&...) noexcept -> debug<Args...>;

template<typename... Args>
struct [[maybe_unused]] info
{
	[[maybe_unused]] info(
	    std::format_string<Args...> format,
	    Args &&...arguments,
	    const std::source_location &location = std::source_location::current()
	) noexcept
	{
		print(Level::info, location, format, std::forward<Args &&>(arguments)...);
	}
};

template<typename... Args>
info(std::format_string<Args...>, Args &&...) noexcept -> info<Args...>;

template<typename... Args>
struct [[maybe_unused]] warn
{
	[[maybe_unused]] warn(
	    std::format_string<Args...> format,
	    Args &&...arguments,
	    const std::source_location &location = std::source_location::current()
	) noexcept
	{
		print(Level::warn, location, format, std::forward<Args &&>(arguments)...);
	}
};

template<typename... Args>
warn(std::format_string<Args...>, Args &&...) noexcept -> warn<Args...>;

template<typename... Args>
struct [[maybe_unused]] error
{
	[[maybe_unused]] error(
	    std::format_string<Args...> format,
	    Args &&...arguments,
	    const std::source_location &location = std::source_location::current()
	) noexcept
	{
		print(Level::error, location, format, std::forward<Args &&>(arguments)...);
	}
};

template<typename... Args>
error(std::format_string<Args...>, Args &&...) noexcept -> error<Args...>;

template<typename... Args>
struct [[maybe_unused]] critical
{
	[[maybe_unused]] critical(
	    std::format_string<Args...> format,
	    Args &&...arguments,
	    const std::source_location &location = std::source_location::current()
	) noexcept
	{
		print(Level::critical, location, format, std::forward<Args &&>(arguments)...);
	}
};

template<typename... Args>
critical(std::format_string<Args...>, Args &&...) noexcept -> critical<Args...>;

} // namespace lt::log
