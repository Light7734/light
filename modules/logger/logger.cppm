export module logger;
import lsd;

namespace lt::log {

auto thread_hash_id() noexcept -> u64
{
	return static_cast<u64>(lsd::hash<lsd::thread_id> {}(lsd::this_thread_id()));
}

} // namespace lt::log

export namespace lt::log {

/** Severity of a log message. */
enum class Level : u8
{
	/** Lowest and most vebose log level, for tracing execution paths and events */
	trace = 0u,

	/** Vebose log level, for enabling temporarily to debug */
	debug = 1u,

	/** General information */
	info = 2u,

	/** Things we should to be aware of and edge cases */
	warn = 3u,

	/** Defects, bugs and undesired behaviour */
	error = 4u,

	/** Unrecoverable errors */
	critical = 5u,

	/** No logging */
	off = 6u,
};

template<typename... Args>
struct [[maybe_unused]] print
{
	[[maybe_unused]] print(
	    Level level,
	    const lsd::src_location &location,
	    lsd::format_str<Args...> format,
	    Args &&...arguments
	) noexcept
	{
		constexpr auto to_string = [](Level level, auto location) {
			// clang-format off
			switch (level)
			{
			using enum ::lt::log::Level;
			case trace   : return "\033[1;37m| trc |\033[0m";
			case debug   : return "\033[1;36m| dbg |\033[0m";
			case info    : return "\033[1;32m| inf |\033[0m";
			case warn    : return "\033[1;33m| wrn |\033[0m";
			case error   : return "\033[1;31m| err |\033[0m";
			case critical: return "\033[1;41m| crt |\033[0m";
			case off: return "off";
			}
			// clang-format on

			lsd::unreachable();
		};

		const auto path = lsd::filesystem::path { location.file_name() };

		lsd::println(
		    "{} {} ==> {}",
		    to_string(level, location),
		    lsd::format("{}:{}", path.filename().string(), location.line()),
		    lsd::format(format, lsd::forward<Args>(arguments)...)
		);
	}
};

template<typename... Args>
print(Level, const lsd::src_location &, lsd::format_str<Args...>, Args &&...) noexcept
    -> print<Args...>;

template<typename... Args>
struct [[maybe_unused]] trace
{
	[[maybe_unused]] trace(
	    lsd::format_str<Args...> format,
	    Args &&...arguments,
	    const lsd::src_location &location = lsd::src_location::current()
	) noexcept
	{
		print(Level::trace, location, format, lsd::forward<Args>(arguments)...);
	}
};

template<typename... Args>
trace(lsd::format_str<Args...>, Args &&...) noexcept -> trace<Args...>;

template<typename... Args>
struct [[maybe_unused]] debug
{
	[[maybe_unused]] debug(
	    lsd::format_str<Args...> format,
	    Args &&...arguments,
	    const lsd::src_location &location = lsd::src_location::current()
	) noexcept
	{
		print(Level::debug, location, format, lsd::forward<Args>(arguments)...);
	}
};

template<typename... Args>
debug(lsd::format_str<Args...>, Args &&...) noexcept -> debug<Args...>;

template<typename... Args>
struct [[maybe_unused]] info
{
	[[maybe_unused]] info(
	    lsd::format_str<Args...> format,
	    Args &&...arguments,
	    const lsd::src_location &location = lsd::src_location::current()
	) noexcept
	{
		print(Level::info, location, format, lsd::forward<Args>(arguments)...);
	}
};

template<typename... Args>
info(lsd::format_str<Args...>, Args &&...) noexcept -> info<Args...>;

template<typename... Args>
struct [[maybe_unused]] warn
{
	[[maybe_unused]] warn(
	    lsd::format_str<Args...> format,
	    Args &&...arguments,
	    const lsd::src_location &location = lsd::src_location::current()
	) noexcept
	{
		print(Level::warn, location, format, lsd::forward<Args>(arguments)...);
	}
};

template<typename... Args>
warn(lsd::format_str<Args...>, Args &&...) noexcept -> warn<Args...>;

template<typename... Args>
struct [[maybe_unused]] error
{
	[[maybe_unused]] error(
	    lsd::format_str<Args...> format,
	    Args &&...arguments,
	    const lsd::src_location &location = lsd::src_location::current()
	) noexcept
	{
		print(Level::error, location, format, lsd::forward<Args>(arguments)...);
	}
};

template<typename... Args>
error(lsd::format_str<Args...>, Args &&...) noexcept -> error<Args...>;

template<typename... Args>
struct [[maybe_unused]] critical
{
	[[maybe_unused]] critical(
	    lsd::format_str<Args...> format,
	    Args &&...arguments,
	    const lsd::src_location &location = lsd::src_location::current()
	) noexcept
	{
		print(Level::critical, location, format, lsd::forward<Args>(arguments)...);
	}
};

template<typename... Args>
critical(lsd::format_str<Args...>, Args &&...) noexcept -> critical<Args...>;

} // namespace lt::log
