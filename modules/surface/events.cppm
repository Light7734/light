export module surface.events;
import math.vec2;
import std;

export namespace lt::surface {

class KeyPressedEvent
{
public:
	KeyPressedEvent(std::uint32_t key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> std::uint32_t
	{
		return m_key;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyPressed: {}", m_key);
	}

private:
	std::uint32_t m_key;
};

class KeyRepeatEvent
{
public:
	KeyRepeatEvent(std::int32_t key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> std::uint32_t
	{
		return m_key;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyRepeated: {}", m_key);
	}

private:
	std::uint32_t m_key;
};

class KeyReleasedEvent
{
public:
	KeyReleasedEvent(std::uint32_t key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> std::uint32_t
	{
		return m_key;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyReleased: {}", m_key);
	}

private:
	std::uint32_t m_key;
};

class KeySetCharEvent
{
public:
	KeySetCharEvent(std::uint32_t character): m_character(character)
	{
	}

	[[nodiscard]] auto get_character() const -> std::uint32_t
	{
		return m_character;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyCharSet: {}", m_character);
	}

private:
	std::uint32_t m_character;
};

class MouseMovedEvent
{
public:
	MouseMovedEvent(float x, float y): m_position(x, y)
	{
	}

	[[nodiscard]] auto get_position() const -> const math::vec2 &
	{
		return m_position;
	}

	[[nodiscard]] auto get_x() const -> float
	{
		return m_position.x;
	}

	[[nodiscard]] auto get_y() const -> float
	{
		return m_position.y;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("MouseMoved: {}, {}", m_position.x, m_position.y);
	}

private:
	math::vec2 m_position;
};

class WheelScrolledEvent
{
public:
	WheelScrolledEvent(float offset): m_offset(offset)
	{
	}

	[[nodiscard]] auto get_offset() const -> float
	{
		return m_offset;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		std::stringstream ss;
		ss << "WheelScrolled: " << m_offset;
		return ss.str();
	}

private:
	float m_offset;
};

class ButtonPressedEvent
{
public:
	ButtonPressedEvent(std::int32_t button): m_button(button)
	{
	}

	[[nodiscard]] auto get_button() const -> std::int32_t
	{
		return m_button;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("ButtonPressed: {}", m_button);
	}

private:
	std::int32_t m_button;
};

class ButtonReleasedEvent
{
public:
	ButtonReleasedEvent(std::int32_t button): m_button(button)
	{
	}

	[[nodiscard]] auto get_button() const -> std::int32_t
	{
		return m_button;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("ButtonReleased: {}", m_button);
	}

private:
	std::int32_t m_button;
};

class ClosedEvent
{
public:
	[[nodiscard]] auto to_string() const -> std::string_view
	{
		return "SurfaceClosedEvent";
	}
};

class MovedEvent
{
public:
	MovedEvent(std::int32_t x, std::int32_t y): m_position(x, y)
	{
	}

	[[nodiscard]] auto get_position() const -> const math::ivec2 &
	{
		return m_position;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		auto stream = std::stringstream {};
		stream << "WindwoMoved: " << m_position.x << ", " << m_position.y;
		return stream.str();
	}

private:
	math::ivec2 m_position;
};

class ResizedEvent
{
public:
	ResizedEvent(std::uint32_t width, std::uint32_t height): m_size(width, height)
	{
	}

	[[nodiscard]] auto get_size() const -> const math::uvec2 &
	{
		return m_size;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		auto stream = std::stringstream {};
		stream << "SurfaceResized: " << m_size.x << ", " << m_size.y;
		return stream.str();
	}

private:
	math::uvec2 m_size;
};

class LostFocusEvent
{
public:
	[[nodiscard]] auto to_string() const -> std::string_view
	{
		return "SurfaceLostFocus";
	}
};

class GainFocusEvent
{
public:
	[[nodiscard]] auto to_string() const -> std::string_view
	{
		return "SurfaceGainFocus";
	}
};

} // namespace lt::surface
