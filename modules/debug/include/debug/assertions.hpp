#pragma once

#include <logger/logger.hpp>

namespace lt {

struct FailedAssertion: std::exception
{
	FailedAssertion(const char *file, int line);
};

// OpenGL
struct glException: std::exception
{
	glException(unsigned int source, unsigned int type, unsigned int id, const char *msg);
};

#define lt_assert(x, ...)                                       \
	{                                                           \
		if (!(x))                                               \
		{                                                       \
			log_crt(__VA_ARGS__);                               \
			throw ::lt::FailedAssertion(__FILE__, __LINE__); \
		}                                                       \
	}

} // namespace lt
