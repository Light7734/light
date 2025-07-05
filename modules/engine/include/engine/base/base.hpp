#pragma once

#include <memory>

namespace Light {

// Ref (Ref)
template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Ref<T> CreateRef(Args &&...args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
constexpr Ref<T> MakeRef(T *rawPointer)
{
	return std::shared_ptr<T>(rawPointer);
}

// Scope (std::unique_ptr)
template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr std::unique_ptr<T> CreateScope(Args &&...args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
constexpr std::unique_ptr<T> MakeScope(T *rawPointer)
{
	return std::unique_ptr<T>(rawPointer);
}

} // namespace Light

//========== PLATFORM ==========//
#define LT_WIN(x) // windows
#define LT_LIN(x) // linux
#define LT_MAC(x) // mac

#if defined(LIGHT_PLATFORM_WINDOWS)
	#define LT_BUILD_PLATFORM "Windows"
	#define LT_WIN(x)         x

#elif defined(LIGHT_PLATFORM_LINUX)
	#define LT_BUILD_PLATFORM "Linux"
	#define LT_LIN(x)         x

#elif defined(LIGHT_PLATFORM_MAC)
	#error "Unsupported platform: MAC"
	#define LT_MAC(x) x

#else
	#error "Unsupported platform: Unknown"
#endif
//========== PLATFORM ==========//

//====================================================================== OPERATIONS
//======================================================================//
/* assertions */
#define ASSERT(x, ...)                                          \
	{                                                           \
		if (!(x))                                               \
		{                                                       \
			LOG(critical, __VA_ARGS__);                         \
			LT_DEBUG_TRAP();                                    \
			throw ::Light::FailedAssertion(__FILE__, __LINE__); \
		}                                                       \
	}

/* bit-wise */
#define BIT(x) 1 << x

/* token */
#define LT_PAIR_TOKEN_VALUE_TO_NAME(token) { token, #token }
#define LT_PAIR_TOKEN_NAME_TO_VALUE(token) { #token, token }
#define LT_TOKEN_NAME(token)               #token
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
