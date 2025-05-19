#pragma once

#include <universal_pch/error_handling/types.hpp>
#include <universal_pch/module_configs.hpp>

namespace lt {

namespace details {

inline void throw_if_false(bool condition, std::source_location location)
{
	if (!condition)
	{
		throw Error { "Failed runtime assertion", location };
	}
}

} // namespace details

/** Throws lt::Error if \a condition is false, otherwise returns without side-effects.
 *
 * @throws lt::Error
 *
 * @note Only runs when LIGHT_ENABLE_CHECK is enabled, which is enabled by default on debug builds.
 *
 * @warn The successful execution of the contract of the using code should NOT depend on the
 * execution of this function as it may or may NOT be executed--based on project configuration.
 */
inline void check(bool condition, std::source_location location = std::source_location::current())
{
	if constexpr (light_enabled_check)
	{
		details::throw_if_false(condition, location);
	}
}

/** Throws lt::Error if \a condition is false, otherwise returns without side-effects.
 *
 * @throws lt::Error
 *
 * @note Only runs when LIGHT_ENABLE_ENSURE is enabled, which is enabled by default on debug and
 * release builds.
 *
 * @warn The successful execution of the contract of the using code should NOT depend on the
 * execution of this function as it may or may NOT be executed--based on project configuration.
 */
inline void ensure(bool condition, std::source_location location = std::source_location::current())
{
	if constexpr (light_enabled_ensure)
	{
		details::throw_if_false(condition, location);
	}
}

} // namespace lt
