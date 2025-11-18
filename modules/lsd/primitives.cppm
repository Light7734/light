export module lsd.primitives;
import std;

/** THIS IS AND SHALL BE THE ONLY NAMESPACE FROM LT
THAT HAS NO SUB-NAMESPACE IDENTIFIER. */
export namespace lt {

using byte = ::std::byte;

using u8 = ::std::uint8_t;
using u16 = ::std::uint16_t;
using u32 = ::std::uint32_t;
using u64 = ::std::uint64_t;

using i8 = ::std::int8_t;
using i16 = ::std::int16_t;
using i32 = ::std::int32_t;
using i64 = ::std::int64_t;

using f32 = float;
using f64 = double;

using size_t = ::std::size_t;

using stream_size = ::std::streamsize;

// The fact that bit_cast is a part of the standard library,
// rather than a builtin like static_cast is language quirk.
//
// From the end-user's perspective, it would be convenient
// for the bit_cast to be a language keyword.
using ::std::bit_cast;

} // namespace lt
