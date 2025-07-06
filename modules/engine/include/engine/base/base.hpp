#pragma once

#include <memory>

namespace Light {

// Ref (Ref)
template<typename t>
using Ref = std::shared_ptr<t>;

template<typename t, typename... Args>
constexpr Ref<t> create_ref(Args &&...args)
{
	return std::make_shared<t>(std::forward<Args>(args)...);
}

template<typename t>
constexpr Ref<t> make_ref(t *rawPointer)
{
	return std::shared_ptr<t>(rawPointer);
}

// Scope (std::unique_ptr)
template<typename t>
using Scope = std::unique_ptr<t>;

template<typename t, typename... Args>
constexpr std::unique_ptr<t> create_scope(Args &&...args)
{
	return std::make_unique<t>(std::forward<Args>(args)...);
}

template<typename t>
constexpr std::unique_ptr<t> make_scope(t *rawPointer)
{
	return std::unique_ptr<t>(rawPointer);
}

} // namespace Light

#define lt_win(x) // windows
#define lt_lin(x) // linux
#define lt_mac(x) // mac


enum class Platform : uint8_t
{
	windows,

	/** Named like so because "linux" is a built-in identifier. */
	gnu,

	mac,
};


namespace constants {

#if defined(LIGHT_PLATFORM_WINDOWS)
	#define lt_win(x) x
constexpr auto platform = Platform::windows;
constexpr auto platform_name = "windows";

#elif defined(LIGHT_PLATFORM_LINUX)
	#define lt_lin(x) x
constexpr auto platform = Platform::gnu;
constexpr auto platform_name = "linux";

#elif defined(LIGHT_PLATFORM_MAC)
	#define lt_mac(x) x
constexpr auto platform = Platform::mac;
constexpr auto platform_name = "mac";

#else
	#error "Unsupported platform: Unknown"

#endif


} // namespace constants

template<typename T = void>
concept is_linux = true;

auto linux_only(auto value)
    requires is_linux<void>
{
	if constexpr (is_linux)
	{
		return value;
	}
}

#define lt_assert(x, ...)                                       \
	{                                                           \
		if (!(x))                                               \
		{                                                       \
			log_crt(__VA_ARGS__);                      \
			lt_debug_trap();                                    \
			throw ::Light::FailedAssertion(__FILE__, __LINE__); \
		}                                                       \
	}

/* bit-wise */
constexpr auto bit(auto x)
{
	return 1 << x;
}

/* token */
#define lt_pair_token_value_to_name(token) { token, #token }
#define lt_pair_token_name_to_value(token) { #token, token }
#define lt_token_name(token)               #token
//====================================================================== OPERATIONS
//======================================================================//

//========== ESSENTIAL_HEADERS ==========//
/* config */
#ifndef LIGHT_CONFIG_H
	#include <engine/base/config.hpp>
#endif

/* debug */
#ifndef LIGHT_LOGGER_H
	#include <engine/debug/logger.hpp>
#endif
#include <engine/debug/exceptions.hpp>

/* portables */
#ifndef LIGHT_DEBUG_TRAP_H
	#include <engine/base/portables/debug_trap.hpp>
#endif

/* utility */
#ifndef LIGHT_STRINGIFIER_H
	#include <engine/utils/stringifier.hpp>
#endif
//========== ESSENTIAL_HEADERS ==========//
