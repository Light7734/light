export module surface.events;

import preliminary;
import input.codes;
import math.vec2;

export namespace lt::surface {

class KeyPressedEvent
{
public:
	KeyPressedEvent(Key key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> Key
	{
		return m_key;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyPressed: {}", std::to_underlying(m_key));
	}

private:
	Key m_key;
};

class KeyRepeatEvent
{
public:
	KeyRepeatEvent(Key key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> Key
	{
		return m_key;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyRepeated: {}", std::to_underlying(m_key));
	}

private:
	Key m_key;
};

class KeyReleasedEvent
{
public:
	KeyReleasedEvent(Key key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> Key
	{
		return m_key;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyReleased: {}", std::to_underlying(m_key));
	}

private:
	Key m_key;
};

class KeySetCharEvent
{
public:
	KeySetCharEvent(Key character): m_character(character)
	{
	}

	[[nodiscard]] auto get_character() const -> Key
	{
		return m_character;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyCharSet: {}", std::to_underlying(m_character));
	}

private:
	Key m_character;
};

class MouseMovedEvent
{
public:
	MouseMovedEvent(f32 x, f32 y): m_position(x, y)
	{
	}

	[[nodiscard]] auto get_position() const -> const math::vec2 &
	{
		return m_position;
	}

	[[nodiscard]] auto get_x() const -> f32
	{
		return m_position.x;
	}

	[[nodiscard]] auto get_y() const -> f32
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
	WheelScrolledEvent(f32 offset): m_offset(offset)
	{
	}

	[[nodiscard]] auto get_offset() const -> f32
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
	f32 m_offset;
};

class ButtonPressedEvent
{
public:
	ButtonPressedEvent(Key button): m_button(button)
	{
	}

	[[nodiscard]] auto get_button() const -> Key
	{
		return m_button;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("ButtonPressed: {}", std::to_underlying(m_button));
	}

private:
	Key m_button;
};

class ButtonReleasedEvent
{
public:
	ButtonReleasedEvent(Key button): m_button(button)
	{
	}

	[[nodiscard]] auto get_button() const -> Key
	{
		return m_button;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("ButtonReleased: {}", std::to_underlying(m_button));
	}

private:
	Key m_button;
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
	MovedEvent(i32 x, i32 y): m_position(x, y)
	{
	}

	[[nodiscard]] auto get_position() const -> const math::ivec2 &
	{
		return m_position;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("WindowMoved: {}, {}", m_position.x, m_position.y);
	}

private:
	math::ivec2 m_position;
};

class ResizedEvent
{
public:
	ResizedEvent(u32 width, u32 height): m_size(width, height)
	{
	}

	[[nodiscard]] auto get_size() const -> const math::uvec2 &
	{
		return m_size;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("SurfaceResized: {}, {}", m_size.x, m_size.y);
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
