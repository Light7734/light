export module memory.reference;

import preliminary;

namespace lt::memory {

/** Wrapper around std::shared_ptr.
 *
 * @note Currently just an alias, might turn into an implementation later.
 * @ref https://en.cppreference.com/w/cpp/memory/shared_ptr.html
 */
export template<typename T>
using Ref = std::shared_ptr<T>;

/** Allocates memory for an `Underlying_T` and directly constructs it there.
 *
 * @return A Ref<Underlying_T> to the constructed object.
 */
export template<typename Underlying_T, typename... Args>
constexpr Ref<Underlying_T> create_ref(Args &&...args)
{
	return std::make_shared<Underlying_T>(std::forward<Args>(args)...);
}

/** Converts c-style pointer of type `Underlying_T` to a `Ref<Underlying_T>`. */
export template<typename Underlying_T>
constexpr Ref<Underlying_T> make_ref(Underlying_T *raw_pointer)
{
	return Ref<Underlying_T>(raw_pointer);
}

} // namespace lt::memory
