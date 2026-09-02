module;

#include <cstdio>
#include <cstdlib>
#include <cxxabi.h>
#include <execinfo.h>
#include <link.h>
#include <unistd.h>

export module preliminary.assertions;

import preliminary.build_constants;
import std;

[[nodiscard]]
auto get_load_base() -> std::uintptr_t
{
	auto base = std::uintptr_t { 0u };
	dl_iterate_phdr(
	    [](struct dl_phdr_info *info, size_t, void *data) {
		    if (info->dlpi_name[0] == '\0') // NOLINT
		    {
			    *static_cast<std::uintptr_t *>(data) = info->dlpi_addr;
			    return 1;
		    }
		    return 0;
	    },
	    &base
	);
	return base;
}

[[nodiscard]]
auto get_backtrace() -> std::string
{
	auto out = std::string {};
	auto buffer = std::array<void *, 5u> {};
	const auto backtrace_count = backtrace(buffer.data(), buffer.size());

	auto exe_path = std::array<char, 4096u> {};
	const auto len = readlink("/proc/self/exe", exe_path.data(), exe_path.size() - 1u);
	exe_path[len > 0 ? len : 0u] = '\0';
	const auto exe_path_view = std::string_view { exe_path.data() };

	const auto base = get_load_base();

	for (auto idx = 0; idx < backtrace_count; ++idx)
	{
		const auto addr = std::bit_cast<std::uintptr_t>(buffer[idx]) - base;
		const auto cmd = std::format("addr2line -e {} -f -C -p {:#x}", exe_path_view, addr);

		auto *pipe = popen(cmd.c_str(), "r");
		if (!pipe)
		{
			continue;
		}

		auto line = std::array<char, 1024u> {};
		while (fgets(line.data(), line.size(), pipe))
		{
			out.append(line.data());
		}
		pclose(pipe);
	}

	return out;
}


/** To be used for ensuring a condition holds true, throws otherwise. */
export template<typename Expression_T, typename... Args_T>
struct ensure
{
	ensure(
	    const Expression_T &expression,
	    std::format_string<Args_T...> fmt,
	    Args_T &&...args,
	    const std::source_location &location = std::source_location::current()
	);
};

/** To be used for costly checks that should be stripped in release builds. */
export template<typename Expression_T, typename... Args_T>
struct debug_check
{
	debug_check(
	    const Expression_T &expression,
	    std::format_string<Args_T...> fmt,
	    Args_T &&...args,
	    const std::source_location &location = std::source_location::current()
	);
};

export template<typename Expression_T, typename... Args_T>
ensure(Expression_T, std::format_string<Args_T...>, Args_T &&...)
    -> ensure<Expression_T, Args_T...>;

export template<typename Expression_T, typename... Args_T>
debug_check(Expression_T, std::format_string<Args_T...>, Args_T &&...)
    -> debug_check<Expression_T, Args_T...>;

template<typename Expression_T, typename... Args_T>
ensure<Expression_T, Args_T...>::ensure(
    const Expression_T &expression,
    std::format_string<Args_T...> fmt,
    Args_T &&...args,
    const std::source_location &location
)
{
	if (!static_cast<bool>(expression))
	{
		throw std::runtime_error { std::format(
			"{}\nlocation: {}:{}\nbacktrace:\n{}",
			std::format(fmt, std::forward<Args_T>(args)...),
			location.file_name(),
			location.line(),
			get_backtrace()
		) };
	}
}

template<typename Expression_T, typename... Args_T>
debug_check<Expression_T, Args_T...>::debug_check(
    const Expression_T &expression,
    std::format_string<Args_T...> fmt,
    Args_T &&...args,
    const std::source_location &location
)
{
	if constexpr (build_constants::build_type != build_constants::BuildType::debug)
	{
		return;
	}

	if (!static_cast<bool>(expression))
	{
		throw std::runtime_error { std::format(
			"{}\nlocation: {}:{}\nbacktrace:\n{}",
			std::format(fmt, std::forward<Args_T>(args)...),
			location.file_name(),
			location.line(),
			get_backtrace()
		) };
	}
}
