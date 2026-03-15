export module logger;

import preliminary;

export namespace lt::log {

/** Severity of a log message. */
enum class Level : u8
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

	/**
	 * Logs from the testing-framework.
	 * Highest so we still get them while turning off all logs from the code under test.
	 *
	 * @note: log::test does NOT include source_location
	 */
	test = 6,

	/** No logging */
	off = 7,
};


} // namespace lt::log

/* private */ namespace lt::log {

class Logger
{
public:
	static void set_severity(Level severity)
	{
		s_min_severity = severity;
	}

	static auto get_severity() -> Level
	{
		return s_min_severity;
	}

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
			std::print("");
			if (std::to_underlying(level) < std::to_underlying(get_severity()))
			{
				return;
			}

			constexpr auto to_string = [](Level level) {
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
            case test: /* testing framework's logs will never have location */
			case off: return "off";
			}
				// clang-format on

				std::unreachable();
			};

			const auto path = std::filesystem::path { location.file_name() };

			std::println(
			    "{} {} ==> {}",
			    to_string(level),
			    std::format("{}:{}", path.filename().string(), location.line()),
			    std::format(format, std::forward<Args>(arguments)...)
			);
		}
	};

	template<typename... Args>
	print(Level, const std::source_location &, std::format_string<Args...>, Args &&...) noexcept
	    -> print<Args...>;

	template<typename... Args>
	static void print_test(std::format_string<Args...> format, Args &&...arguments) noexcept
	{
		std::println(
		    "\033[1;33m| test |\033[0m {}",
		    std::format(format, std::forward<Args>(arguments)...)
		);
	}


private:
	static Level s_min_severity;
};
auto Logger::s_min_severity = Level::trace;

} // namespace lt::log

export namespace lt::log {

void set_severity(Level level)
{
	Logger::set_severity(level);
}

auto get_severity() -> Level
{
	return Logger::get_severity();
}

template<typename... Args>
struct [[maybe_unused]] trace
{
	[[maybe_unused]] trace(
	    std::format_string<Args...> format,
	    Args &&...arguments,
	    const std::source_location &location = std::source_location::current()
	) noexcept
	{
		Logger::print(Level::trace, location, format, std::forward<Args>(arguments)...);
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
		Logger::print(Level::debug, location, format, std::forward<Args>(arguments)...);
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
		Logger::print(Level::info, location, format, std::forward<Args>(arguments)...);
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
		Logger::print(Level::warn, location, format, std::forward<Args>(arguments)...);
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
		Logger::print(Level::error, location, format, std::forward<Args>(arguments)...);
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
		Logger::print(Level::critical, location, format, std::forward<Args>(arguments)...);
	}
};

template<typename... Args>
critical(std::format_string<Args...>, Args &&...) noexcept -> critical<Args...>;

template<typename... Args>
struct [[maybe_unused]] test
{
	[[maybe_unused]] test(std::format_string<Args...> format, Args &&...arguments) noexcept
	{
		Logger::print_test(format, std::forward<Args>(arguments)...);
	}
};

template<typename... Args>
test(std::format_string<Args...>, Args &&...) noexcept -> test<Args...>;

} // namespace lt::log
