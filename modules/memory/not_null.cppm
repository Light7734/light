export module memory.not_null;

import preliminary;

template<typename T>
using value_or_reference_return_t = std::conditional_t<
    std::is_trivially_copy_constructible_v<T> && sizeof(T) <= sizeof(void *) * 2,
    const T,
    const T &>;

export namespace lt::memory {

/** Makes your code crash when using nullptrs on bind-point instead of dereference point.
 * Makes debugging easier in case of a logical error.
 * Also removes the "is this a nullptr?" checks as it is now implied through construction.
 * Has 0 zero-size-overhead over Underlying_T.
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
template<typename Underlying_T>
    requires(std::is_assignable_v<Underlying_T &, std::nullptr_t>)
class NotNull
{
public:
	/** Constructs from anything convertible to Underlying_T (raw pointer, smart pointer, etc.) */
	template<typename Ptr_T>
	constexpr explicit NotNull(Ptr_T &&pointer)
	    requires std::is_convertible_v<Ptr_T, Underlying_T>
	    : m_ptr(std::forward<Ptr_T>(pointer))
	{
		ensure(m_ptr != nullptr, "Bound a NotNull ptr to a nullptr!");
	}

	/** DISALLOW construction via nullptr_t */
	NotNull(std::nullptr_t) = delete;

	/** DISALLOW assignment to nullptr_t */
	NotNull &operator=(std::nullptr_t) = delete;

	/** Default move constructor */
	NotNull(NotNull &&) = default;

	/** Default copy constructor */
	NotNull(const NotNull &) = default;

	/** Default move assignment operator */
	NotNull &operator=(NotNull &&) = default;

	/** Default copy assignment operator */
	NotNull &operator=(const NotNull &) = default;

	~NotNull() = default;

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

	/** Swaps the underlying pointers */
	void swap(NotNull<Underlying_T> &other) noexcept
	{
		std::swap(m_ptr, other.m_ptr);
	}

	/** DISALLOW pointer arithmetic */
	NotNull &operator++() = delete;

	/** DISALLOW pointer arithmetic */
	NotNull &operator--() = delete;

	/** DISALLOW pointer arithmetic */
	NotNull operator++(int) = delete;

	/** DISALLOW pointer arithmetic */
	NotNull operator--(int) = delete;

	/** DISALLOW pointer arithmetic */
	NotNull &operator+=(std::ptrdiff_t) = delete;

	/** DISALLOW pointer arithmetic */
	NotNull &operator-=(std::ptrdiff_t) = delete;

	/** DISALLOW pointer arithmetic */
	void operator[](std::ptrdiff_t) const = delete;

	/** DISALLOW pointer arithmetic */
	template<class T, class U>
	friend std::ptrdiff_t operator-(const NotNull<T> &, const NotNull<U> &) = delete;

	/** DISALLOW pointer arithmetic */
	template<class T>
	friend NotNull<T> operator-(const NotNull<T> &, std::ptrdiff_t) = delete;

	/** DISALLOW pointer arithmetic */
	template<class T>
	friend NotNull<T> operator+(const NotNull<T> &, std::ptrdiff_t) = delete;

	/** DISALLOW pointer arithmetic */
	template<class T>
	friend NotNull<T> operator+(std::ptrdiff_t, const NotNull<T> &) = delete;

private:
	Underlying_T m_ptr;
};

template<typename T, typename U>
constexpr bool operator==(const NotNull<T> &lhs, const NotNull<U> &rhs)
{
	return lhs.get() == rhs.get();
}

template<typename T, typename U>
constexpr bool operator!=(const NotNull<T> &lhs, const NotNull<U> &rhs)
{
	return !(lhs == rhs);
}

} // namespace lt::memory
