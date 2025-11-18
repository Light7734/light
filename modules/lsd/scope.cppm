export module lsd.scope_ptr;
import std;

export namespace lt::lsd {

/** Wrapper around std::unique_ptr.
 *
 * @note Currently just an alias, might turn into an implementation later.
 * @ref https://en.cppreference.com/w/cpp/memory/unique_ptr.html
 */
template<typename t>
using scope = std::unique_ptr<t>;

/** Allocates memory for an `Underlying_T` and directly constructs it there.
 *
 * @return A Scope<Underlying_T> to the constructed object.
 */
template<typename Underlying_T, typename... Args>
constexpr auto create_scope(Args &&...args) -> scope<Underlying_T>
{
	return std::make_unique<Underlying_T>(std::forward<Args>(args)...);
}

/** Converts c-style pointer of type `Underlying_T` to a `Scope<Underlying_T>`. */
template<typename Underlying_T>
constexpr auto make_scope(Underlying_T *raw_pointer) -> scope<Underlying_T>
{
	return scope<Underlying_T>(raw_pointer);
}

} // namespace lt::lsd
