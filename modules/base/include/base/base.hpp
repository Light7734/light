#pragma once

#include <memory>

namespace lt {

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

} // namespace lt

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

/* bit-wise */
constexpr auto bit(auto x)
{
	return 1 << x;
}

/* token */
#define lt_pair_token_value_to_name(token) { token, #token }
#define lt_pair_token_name_to_value(token) { #token, token }
#define lt_token_name(token)               #token
