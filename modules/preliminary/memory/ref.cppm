export module preliminary.memory.ref;

import preliminary.fundumental_types;
import preliminary.concepts;
import preliminary.assertions;
import preliminary.build_constants;
import std;

/** Wrapper around std::shared_ptr.
 *
 * @note Currently just an alias, might turn into an implementation later.
 * @ref https://en.cppreference.com/w/cpp/memory/shared_ptr.html
 */
export template<typename T>
using ref = std::shared_ptr<T>;

/** Allocates memory for an `Underlying_T` and directly constructs it there.
 *
 * @return A ref<Underlying_T> to the constructed object.
 */
export template<typename Underlying_T, typename... Args>
constexpr ref<Underlying_T> create_ref(Args &&...args)
{
	return std::make_shared<Underlying_T>(std::forward<Args>(args)...);
}

/** Converts c-style pointer of type `Underlying_T` to a `ref<Underlying_T>`. */
export template<typename Underlying_T>
constexpr ref<Underlying_T> make_ref(Underlying_T *raw_pointer)
{
	return ref<Underlying_T>(raw_pointer);
}
