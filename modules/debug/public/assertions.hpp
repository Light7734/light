#pragma once

#include <format>
#include <logger/logger.hpp>
#include <source_location>

namespace lt {

struct FailedAssertion: std::exception
{
	FailedAssertion(const char *file, int line)
	{
		log_crt("Assertion failed in: {} (line {})", file, line);
	}
};


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
