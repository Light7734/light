export module preliminary.build_constants;

import preliminary.fundumental_types;
import std;

export namespace build_constants {

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

enum class BuildType : u8
{
	debug,
	release,
	distribution
};

constexpr auto platform = Platform::gnu_linux;
constexpr auto platform_name = "gnu_linux";
constexpr auto platform_identifier = platform_name; // TODO(Light)

/** @TODO(Light): Handle other compilers... */
#ifdef __clang__
constexpr auto compiler = Compiler::clang;
constexpr auto compiler_name = "clang";

/** @TODO(Light): insert the full identifier, including version information and such */
constexpr auto compiler_identifier = "clang";
#endif

// @TODO(Light): inject build info through CMake using LIGHT_... constant macros
#if defined(_DEBUG)
constexpr auto build_type = BuildType::debug;
#else
constexpr auto build_type = BuildType::release;
#endif

} // namespace build_constants
