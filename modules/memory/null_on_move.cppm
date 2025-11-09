export module memory.null_on_move;

import std;

namespace lt::memory {

/** Holds an `Underlying_T`, assigns it to `null_value` when this object is moved.
 *
 * @note For avoiding the need to explicitly implement the move constructor for objects that hold
 * Vulkan objects. But may serve other purposes, hence why I kept the implementation generic.
 */
export template<typename Underlying_T, Underlying_T null_value = nullptr>
class NullOnMove
{
public:
	NullOnMove() = default;

	NullOnMove(Underlying_T value): m_value(value)
	{
	}

	~NullOnMove() = default;

	NullOnMove(const NullOnMove &) = delete;

	auto operator=(const NullOnMove &) -> NullOnMove & = delete;

	NullOnMove(NullOnMove &&other) noexcept
	{
		*this = std::move(other);
	}

	auto operator=(NullOnMove &&other) noexcept -> NullOnMove &
	{
		if (this == std::addressof(other))
		{
			return *this;
		}

		m_value = other.m_value;
		other.m_value = null_value;

		return *this;
	}

	auto operator->() -> Underlying_T
	{
		return m_value;
	}

	// NOLINTNEXTLINE
	auto operator->() const -> const Underlying_T
	{
		return m_value;
	}

	auto operator&() const -> const Underlying_T *
	{
		return &m_value;
	}

	auto operator&() -> Underlying_T *
	{
		return &m_value;
	}

	operator bool() const
	{
		return m_value != null_value;
	}

	operator Underlying_T() const
	{
		return m_value;
	}

	operator Underlying_T()
	{
		return m_value;
	}

	operator std::uint64_t() const
	{
		return (std::uint64_t)m_value;
	}

	[[nodiscard]] auto get() -> Underlying_T &
	{
		return m_value;
	}

	[[nodiscard]] auto get() const -> const Underlying_T &
	{
		return m_value;
	}

private:
	Underlying_T m_value;
};

} // namespace lt::memory
