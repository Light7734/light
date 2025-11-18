export module env;
import lsd;

export namespace lt {

enum class Platform : u8
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
enum class Compiler : u8
{
	clang,
	gcc,
	msvc,
	apple_clang,
};

namespace constants {

#define lt_windows_only(x)
#define lt_linux_only(x)
#define lt_mac_only(x)

#if defined(LIGHT_PLATFORM_WINDOWS)
    // NOLINTNEXTLINE
	#define lt_windows_only(x) x
constexpr auto platform = Platform::windows;
constexpr auto platform_name = "windows";

#elif defined(LIGHT_PLATFORM_LINUX)
    // NOLINTNEXTLINE
	#define lt_linux_only(x) x
constexpr auto platform = Platform::gnu_linux;
constexpr auto platform_name = "gnu_linux";

#elif defined(LIGHT_PLATFORM_MAC)
    // NOLINTNEXTLINE
	#define lt_mac_only(x) x
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
