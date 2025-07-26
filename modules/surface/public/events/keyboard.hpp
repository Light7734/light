#pragma once

#include <format>

namespace lt::surface {

class KeyPressedEvent
{
public:
	KeyPressedEvent(int32_t key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> int32_t
	{
		return m_key;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyPressed: {}", m_key);
	}

private:
	int32_t m_key;
};

class KeyRepeatEvent
{
public:
	KeyRepeatEvent(int key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> int32_t
	{
		return m_key;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyRepeated: {}", m_key);
	}

private:
	int32_t m_key;
};

class KeyReleasedEvent
{
public:
	KeyReleasedEvent(int key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> int32_t
	{
		return m_key;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyReleased: {}", m_key);
	}

private:
	int32_t m_key;
};

class KeySetCharEvent
{
public:
	KeySetCharEvent(uint32_t character): m_character(character)
	{
	}

	[[nodiscard]] auto get_character() const -> uint32_t
	{
		return m_character;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("KeyCharSet: {}", m_character);
	}

private:
	uint32_t m_character;
};

} // namespace lt::surface
