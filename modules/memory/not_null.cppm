export module memory.not_null;

import preliminary;

export namespace lt::memory {

template<typename Underlying_T>
class NotNull
{
	static_assert(
	    std::is_assignable_v<Underlying_T &, std::nullptr_t>,
	    "Underlying_T must be a type that can be compared/assigned to nullptr (e.g. a pointer)."
	);

public:
	// Construct from anything convertible to T (raw pointer, smart pointer, etc.)
	template<typename Ptr_T>
	constexpr NotNull(Ptr_T &&pointer)
	    requires std::is_convertible_v<Ptr_T, Underlying_T>
	    : m_ptr(std::forward<Ptr_T>(pointer))
	{
		ensure(m_ptr, "Bound a NotNull ptr to a nullptr!");
	}

	// Explicitly forbid the obvious ways to sneak a null in.
	NotNull(std::nullptr_t) = delete;

	NotNull &operator=(std::nullptr_t) = delete;

	NotNull(NotNull &&) = default;

	NotNull(const NotNull &) = default;

	NotNull &operator=(NotNull &&) = default;

	NotNull &operator=(const NotNull &) = default;

	~NotNull() = default;

	constexpr Underlying_T get() const noexcept
	{
		return m_ptr;
	}
	constexpr operator Underlying_T() const noexcept
	{
		return get();
	}
	constexpr Underlying_T operator->() const noexcept
	{
		return get();
	}
	constexpr decltype(auto) operator*() const
	{
		return *get();
	}

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
