export module preliminary.memory.scope;

import preliminary.fundumental_types;
import preliminary.concepts;
import preliminary.assertions;
import preliminary.build_constants;
import std;

/** @brief Wrapper around std::unique_ptr.
 *
 * @note Currently just an alias, might turn into an implementation later.
 * @ref https://en.cppreference.com/w/cpp/memory/unique_ptr.html
 */
export template<typename t>
using scope = std::unique_ptr<t>;

/** Allocates memory for an `Underlying_T` and directly constructs it there.
 *
 * @return A scope<Underlying_T> to the constructed object.
 */
export template<typename Underlying_T, typename... Args>
constexpr scope<Underlying_T> create_scope(Args &&...args)
{
	return std::make_unique<Underlying_T>(std::forward<Args>(args)...);
}

/** Converts c-style pointer of type `Underlying_T` to a `scope<Underlying_T>`. */
export template<typename Underlying_T>
constexpr scope<Underlying_T> make_scope(Underlying_T *raw_pointer)
{
	return scope<Underlying_T>(raw_pointer);
}
