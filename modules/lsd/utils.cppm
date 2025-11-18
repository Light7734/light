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
using ::std::bit_cast;
using ::std::declval;
using ::std::format;
using ::std::forward;
using ::std::move;
using ::std::println;
using ::std::system;
using ::std::to_underlying;

// NOLINTEND

} // namespace lt::lsd
