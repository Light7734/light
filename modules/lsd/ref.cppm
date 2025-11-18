export module lsd.ref_ptr;

import std;

export namespace lt::lsd {

/** Wrapper around std::shared_ptr.
 *
 * @note Currently just an alias, might turn into an implementation later.
 * @ref https://en.cppreference.com/w/cpp/memory/shared_ptr.html
 */
template<typename T>
using ref = std::shared_ptr<T>;

/** Allocates memory for an `Underlying_T` and directly constructs it there.
 *
 * @return A Ref<Underlying_T> to the constructed object.
 */
template<typename Underlying_T, typename... Args>
constexpr auto create_ref(Args &&...args) -> ref<Underlying_T>
{
	return std::make_shared<Underlying_T>(std::forward<Args>(args)...);
}

/** Converts c-style pointer of type `Underlying_T` to a `Ref<Underlying_T>`. */
template<typename Underlying_T>
constexpr auto make_ref(Underlying_T *raw_pointer) -> ref<Underlying_T>
{
	return ref<Underlying_T>(raw_pointer);
}

} // namespace lt::lsd
