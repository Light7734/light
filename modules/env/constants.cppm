export module env;

import std;

namespace lt {

enum class Platform : std::uint8_t
{
	/** The GNU/Linux platform.
	 * Tested on the following distros: arch-x86_64
	 * @note: Named like so because `linux` is a built-in identifier.
	 * */
	gnu_linux,

	/**
	 * The Microsoft Windows(tm) platform.
	 * Tested on the following architectures: x86_64
	 */
	windows,

	/**
	 * The apple's macOS platform.
	 * Currently not supported.
	 */
	mac,
};

/** The compiler that was used for compiling the project. */
enum class Compiler : std::uint8_t
{
	clang,
	gcc,
	msvc,
	apple_clang,
};

namespace constants {

#if defined(LIGHT_PLATFORM_WINDOWS)
	#define lt_win(x)
constexpr auto platform = Platform::windows;
constexpr auto platform_name = "windows";

	#undef LIGHT_PLATFORM_WINDOWS

#elif defined(LIGHT_PLATFORM_LINUX)
constexpr auto platform = Platform::gnu_linux;
constexpr auto platform_name = "gnu_linux";

#elif defined(LIGHT_PLATFORM_MAC)
	#define lt_mac(x) x
constexpr auto platform = Platform::mac;
constexpr auto platform_name = "mac";

#else
	#error "Unsupported platform: Unknown"

#endif

#ifdef __clang__
constexpr auto compiler = Compiler::clang;
constexpr auto compiler_name = "clang";

/** @todo(Light): insert the full identifier, including version information and such */
constexpr auto full_compiler_identifier = "clang";
#endif

} // namespace constants

} // namespace lt
