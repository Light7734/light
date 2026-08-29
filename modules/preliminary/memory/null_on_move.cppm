export module preliminary.memory.null_on_move;

import preliminary.fundumental_types;
import preliminary.concepts;
import preliminary.assertions;
import preliminary.build_constants;
import std;

/** Holds an `Underlying_T`, assigns it to `null_value` when this object is moved.
 *
 * @note For avoiding the need to explicitly implement the move constructor for objects that hold
 * non-raii-handles (eg. Vulkan, Wayland).
 */
export template<typename Underlying_T, Underlying_T null_value = nullptr>
class null_on_move
{
public:
	null_on_move() = default;

	null_on_move(Underlying_T value): m_value(value)
	{
	}

	~null_on_move() = default;

	null_on_move(const null_on_move &) = delete;

	auto operator=(const null_on_move &) -> null_on_move & = delete;

	null_on_move(null_on_move &&other) noexcept
	{
		*this = std::move(other);
	}

	auto operator=(null_on_move &&other) noexcept -> null_on_move &
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
