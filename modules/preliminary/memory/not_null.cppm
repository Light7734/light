export module preliminary.memory.not_null;

import preliminary.fundumental_types;
import preliminary.concepts;
import preliminary.assertions;
import preliminary.build_constants;
import std;

template<typename T>
using value_or_reference_return_t = std::conditional_t<
    std::is_trivially_copy_constructible_v<T> && sizeof(T) <= sizeof(void *) * 2,
    const T,
    const T &>;

/** Makes your code crash when using nullptrs on bind-point instead of dereference point.
 * Which should make debugging easier in case of a logical error.
 * Also removes the "is this a nullptr?" checks as it is now implied through construction.
 * Has 0 zero-size-overhead over Underlying_T.
 *
 * The constructor is explicit so that when T* changes to not_null<T*>, the call-sites that used the
 * old T* form stop compiling and require explicitly specifying that they indeed understand the
 * passed point should not be null
 *
 * ALLOWS construction from Underlying_T (which MUST be nullptr assignable)
 * ALLOWS implicit conversion to Underlying_T
 * DISALLOWS default construction
 * DISALLOWS construction from nullptr_t
 * DISALLOWS pointer arithmetics
 * THROWS when constructing an Underlying_T with a nullptr
 *
 * @tparam Underlying_T The underlying pointer type
 */
export template<typename Underlying_T>
    requires(std::is_assignable_v<Underlying_T &, std::nullptr_t>)
class not_null
{
public:
	/** Constructs from anything convertible to Underlying_T (raw pointer, smart pointer, etc.)
	 *
	 * @warn Explicit
	 */
	template<typename Ptr_T>
	constexpr explicit not_null(Ptr_T &&pointer)
	    requires std::is_convertible_v<Ptr_T, Underlying_T>
	    : m_ptr(std::forward<Ptr_T>(pointer))
	{
		ensure(m_ptr != nullptr, "Bound a not_null ptr to a nullptr!");
	}

	/** DISALLOW construction via nullptr_t */
	not_null(std::nullptr_t) = delete;

	/** DISALLOW assignment to nullptr_t */
	not_null &operator=(std::nullptr_t) = delete;

	/** Default move constructor */
	not_null(not_null &&) = default;

	/** Default copy constructor */
	not_null(const not_null &) = default;

	/** Default move assignment operator */
	not_null &operator=(not_null &&) = default;

	/** Default copy assignment operator */
	not_null &operator=(const not_null &) = default;

	~not_null() = default;

	/** Returns the underlying pointer.
	 * `value_or_reference_return_t` is used because a wrapped `unique_ptr` can only be
	 * returned through a reference.
	 */
	constexpr auto get() const noexcept(
	    noexcept(value_or_reference_return_t<Underlying_T>(std::declval<Underlying_T &>()))
	) -> value_or_reference_return_t<Underlying_T>
	{
		return m_ptr;
	}

	/** Implicit conversion to `Underlying_T` */
	constexpr operator Underlying_T() const
	{
		return get();
	}

	/** Implicit conversion to `Underlying_T` via the arrow operator */
	constexpr decltype(auto) operator->() const
	{
		return get();
	}

	/** Implicit conversion to `decltype(*Underlying_T)` via dereferencing */
	constexpr decltype(auto) operator*() const
	{
		return *get();
	}

	/** Equality comparison operator */
	constexpr friend auto operator==(
	    const not_null<Underlying_T> &lhs,
	    const not_null<Underlying_T> &rhs
	) -> bool
	{
		return lhs.get() == rhs.get();
	}

	/** Unequality comparison */
	constexpr friend auto operator!=(
	    const not_null<Underlying_T> &lhs,
	    const not_null<Underlying_T> &rhs
	) -> bool
	{
		return !(lhs == rhs);
	}

	/** Swaps the underlying pointers */
	void swap(not_null<Underlying_T> &other) noexcept
	{
		std::swap(m_ptr, other.m_ptr);
	}

	/** DISALLOW pointer arithmetic */
	not_null &operator++() = delete;

	/** DISALLOW pointer arithmetic */
	not_null &operator--() = delete;

	/** DISALLOW pointer arithmetic */
	not_null operator++(int) = delete;

	/** DISALLOW pointer arithmetic */
	not_null operator--(int) = delete;

	/** DISALLOW pointer arithmetic */
	not_null &operator+=(std::ptrdiff_t) = delete;

	/** DISALLOW pointer arithmetic */
	not_null &operator-=(std::ptrdiff_t) = delete;

	/** DISALLOW pointer arithmetic */
	void operator[](std::ptrdiff_t) const = delete;

	/** DISALLOW pointer arithmetic */
	friend std::ptrdiff_t operator-(
	    const not_null<Underlying_T> &,
	    const not_null<Underlying_T> &
	) = delete;

	/** DISALLOW pointer arithmetic */
	friend not_null<Underlying_T> operator-(
	    const not_null<Underlying_T> &,
	    std::ptrdiff_t
	) = delete;

	/** DISALLOW pointer arithmetic */
	friend not_null<Underlying_T> operator+(
	    const not_null<Underlying_T> &,
	    std::ptrdiff_t
	) = delete;

	/** DISALLOW pointer arithmetic */
	friend not_null<Underlying_T> operator+(
	    std::ptrdiff_t,
	    const not_null<Underlying_T> &
	) = delete;

private:
	Underlying_T m_ptr;
};

template<class T>
not_null(T) -> not_null<T>;
