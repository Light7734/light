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

//========== PLATFORM ==========//
#define lt_win(x) // windows
#define lt_lin(x) // linux
#define lt_mac(x) // mac

#if defined(LIGHT_PLATFORM_WINDOWS)
	#define LT_BUILD_PLATFORM "Windows"
	#define lt_win(x)         x

#elif defined(LIGHT_PLATFORM_LINUX)
	#define LT_BUILD_PLATFORM "Linux"
	#define lt_lin(x)         x

#elif defined(LIGHT_PLATFORM_MAC)
	#error "Unsupported platform: MAC"
	#define lt_mac(x) x

#else
	#error "Unsupported platform: Unknown"
#endif
//========== PLATFORM ==========//

//====================================================================== OPERATIONS
//======================================================================//
/* assertions */
#define lt_assert(x, ...)                                          \
	{                                                           \
		if (!(x))                                               \
		{                                                       \
			lt_log(critical, __VA_ARGS__);                         \
			lt_debug_trap();                                    \
			throw ::Light::FailedAssertion(__FILE__, __LINE__); \
		}                                                       \
	}

/* bit-wise */
#define bit(x) 1 << x

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
