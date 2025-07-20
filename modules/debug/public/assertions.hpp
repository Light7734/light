#pragma once

#include <logger/logger.hpp>

namespace lt {

struct FailedAssertion: std::exception
{
	FailedAssertion(const char *file, int line)
	{
		log_crt("Assertion failed in: {} (line {})", file, line);
	}
};


template<typename Expression_T, typename... Args>
constexpr void ensure(Expression_T &&expression, std::format_string<Args...> fmt, Args &&...args)
{
	if (!static_cast<bool>(expression))
	{
		Logger::log(LogLvl::critical, fmt, std::forward<Args>(args)...);
		throw ::lt::FailedAssertion(__FILE__, __LINE__);
	}
}

template<typename Expression_T>
constexpr void ensure(Expression_T &&expression, const char *message)
{
	if (!static_cast<bool>(expression))
	{
		Logger::log(LogLvl::critical, message);
		throw ::lt::FailedAssertion(__FILE__, __LINE__);
	}
}

} // namespace lt
