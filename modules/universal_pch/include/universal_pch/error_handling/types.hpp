#pragma once

namespace lt {

class Error: public std::exception
{
public:
	Error(std::string_view reason, std::source_location location): m_reason(reason)
	{
		std::ignore = location;
	}

	Error(const Error &prev, std::string_view reason, std::source_location location)
	    : m_reason(reason)
	{
		std::ignore = location;
		std::ignore = prev;
	}

	[[nodiscard]] auto what() const noexcept -> const char * override
	{
		return "Idk fuck all";
	}

private:
	std::string m_reason;
};

template<typename T>
using Expected = std::expected<T, Error>;
} // namespace lt
