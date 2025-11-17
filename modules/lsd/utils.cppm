export module lsd.utils;
import std;

export namespace lt::lsd {

[[noreturn]] void unreachable() noexcept
{
#if defined(__clang__) || defined(__GNUC__)
	__builtin_unreachable();
#elif defined(_MSC_VER)
	std::terminate();
	__assume(0);
#else
	std::terminate();
#endif
}

// NOLINTBEGIN
using ::std::declval;
using ::std::format;
using ::std::forward;
using ::std::move;
using ::std::println;

namespace filesystem {

using ::std::filesystem::path;

}
// NOLINTEND

} // namespace lt::lsd
