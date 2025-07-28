#pragma once

#include <concepts>
#include <format>
#include <source_location>

namespace lt::test {

template<typename T>
concept Printable = requires(std::ostream &os, T t) {
	{ os << t } -> std::same_as<std::ostream &>;
};

template<typename T>
concept Testable = Printable<T> && std::equality_comparable<T>;

constexpr void expect_unreachable(
    std::source_location source_location = std::source_location::current()
)
{
	throw std::runtime_error {
		std::format(
		    "Failed unreachable expectation:\n"
		    "\tlocation: {}:{}",
		    source_location.file_name(),
		    source_location.line()
		),
	};
};

constexpr void expect_throw(
    std::invocable auto invocable,
    std::source_location source_location = std::source_location::current()
)
{
	try
	{
		invocable();
	}
	catch (const std::exception &exp)
	{
		return;
	}

	throw std::runtime_error {
		std::format(
		    "Failed throwing expectation:\n"
		    "\tlocation: {}:{}",
		    source_location.file_name(),
		    source_location.line()
		),
	};
}

constexpr void expect_eq(
    Testable auto lhs,
    Testable auto rhs,
    std::source_location source_location = std::source_location::current()
)
{
	if (lhs != rhs)
	{
		throw std::runtime_error {
			std::format(
			    "Failed equality expectation:\n"
			    "\tactual: {}\n"
			    "\texpected: {}\n"
			    "\tlocation: {}:{}",
			    lhs,
			    rhs,
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

constexpr void expect_ne(
    Testable auto lhs,
    Testable auto rhs,
    std::source_location source_location = std::source_location::current()
)
{
	if (lhs == rhs)
	{
		throw std::runtime_error {
			std::format(
			    "Failed un-equality expectation:\n"
			    "\tactual: {}\n"
			    "\texpected: {}\n"
			    "\tlocation: {}:{}",
			    lhs,
			    rhs,
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

constexpr void expect_true(
    bool expression,
    std::source_location source_location = std::source_location::current()
)
{
	if (!expression)
	{
		throw std::runtime_error {
			std::format(
			    "Failed true expectation:\n"
			    "\tactual: {}\n"
			    "\texpected: true\n"
			    "\tlocation: {}:{}",
			    expression,
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

constexpr void expect_false(
    bool expression,
    std::source_location source_location = std::source_location::current()
)
{
	if (expression)
	{
		throw std::runtime_error {
			std::format(
			    "Failed false expectation:\n"
			    "\tactual: {}\n"
			    "\texpected: true\n"
			    "\tlocation: {}:{}",
			    expression,
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

constexpr void expect_not_nullptr(
    auto *pointer,
    std::source_location source_location = std::source_location::current()
)
{
	if (pointer == nullptr)
	{
		throw std::runtime_error {
			std::format(
			    "Failed true expectation:\n"
			    "\tactual: nullptr\n"
			    "\texpected: not nullptr\n"
			    "\tlocation: {}:{}",
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}


constexpr void expect_le(
    Testable auto lhs,
    Testable auto rhs,
    std::source_location source_location = std::source_location::current()
)
{
	if (lhs > rhs)
	{
		throw std::runtime_error {
			std::format(
			    "Failed false expectation:\n"
			    "\tactual: {}\n"
			    "\texpected: >= {}\n"
			    "\tlocation: {}:{}",
			    lhs,
			    rhs,
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

} // namespace lt::test
