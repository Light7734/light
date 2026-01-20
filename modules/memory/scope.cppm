export module memory.scope;

import preliminary;

namespace lt::memory {

/** @brief Wrapper around std::unique_ptr.
 *
 * @note Currently just an alias, might turn into an implementation later.
 * @ref https://en.cppreference.com/w/cpp/memory/unique_ptr.html
 */
export template<typename t>
using Scope = std::unique_ptr<t>;

/** Allocates memory for an `Underlying_T` and directly constructs it there.
 *
 * @return A Scope<Underlying_T> to the constructed object.
 */
export template<typename Underlying_T, typename... Args>
constexpr Scope<Underlying_T> create_scope(Args &&...args)
{
	return std::make_unique<Underlying_T>(std::forward<Args>(args)...);
}

/** Converts c-style pointer of type `Underlying_T` to a `Scope<Underlying_T>`. */
export template<typename Underlying_T>
constexpr Scope<Underlying_T> make_scope(Underlying_T *raw_pointer)
{
	return Scope<Underlying_T>(raw_pointer);
}

} // namespace lt::memory
