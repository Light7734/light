export module test.expects;

import preliminary;

template<typename T>
concept Formattable = requires(T &v, std::format_context ctx) {
	std::formatter<std::remove_cvref_t<T>>().format(v, ctx);
};

template<typename T>
concept Printable = Formattable<T> || requires(std::ostream &stream, T value) {
	{ stream << std::to_underlying<T>(value) } -> std::same_as<std::ostream &>;
};

template<typename T>
concept Testable = (Printable<T> || std::is_pointer_v<T>) && std::equality_comparable<T>;

export namespace lt::test {

/** Fails the test case when gets called. */
void expect_unreachable(std::source_location source_location = std::source_location::current());

/** Fails the test case when no exceptions are thrown in @a invocable.
 *
 * @todo: Check exception type.
 */
void expect_throw(
    std::invocable auto invocable,
    std::source_location source_location = std::source_location::current()
);

/** Fails the test case when `lhs != rhs`. */
void expect_eq(
    Testable auto lhs,
    Testable auto rhs,
    std::source_location source_location = std::source_location::current()
);

/** Fails the test case when `lhs == rhs`. */
void expect_ne(
    Testable auto lhs,
    Testable auto rhs,
    std::source_location source_location = std::source_location::current()
);

/** Fails the test case when `lhs > rhs`. */
void expect_le(
    Testable auto lhs,
    Testable auto rhs,
    std::source_location source_location = std::source_location::current()
);

/** Fails the test case when `lhs < rhs`. */
void expect_ge(
    Testable auto lhs,
    Testable auto rhs,
    std::source_location source_location = std::source_location::current()
);

/** Fails the test case when @a expression is `false`. */
void expect_true(
    bool expression,
    std::source_location source_location = std::source_location::current()
);

/** Fails the test case when @a expression is `true`. */
void expect_false(
    bool expression,
    std::source_location source_location = std::source_location::current()
);

/** Fails the test case when `pointer == nullptr`. */
void expect_not_nullptr(
    auto *pointer,
    std::source_location source_location = std::source_location::current()
);

/** Fails the test case when @a string does not contain @a token. */
void expect_str_contains(
    const std::string &string,
    const std::string &token,
    std::source_location source_location = std::source_location::current()
);

} // namespace lt::test

namespace lt::test {

void expect_unreachable(
    std::source_location source_location /* = std::source_location::current() */
)
{
	throw std::runtime_error {
		std::format(
		    "unreachable reached: {}:{}",
		    source_location.file_name(),
		    source_location.line()
		),
	};
};

void expect_throw(
    std::invocable auto invocable,
    std::source_location source_location /* = std::source_location::current() */
)
{
	try
	{
		invocable();
	}
	catch (const std::exception &)
	{
		return;
	}

	throw std::runtime_error {
		std::format("did not throw: {}:{}", source_location.file_name(), source_location.line()),
	};
}

/** Fails the test case when `lhs != rhs`. */
void expect_eq(
    Testable auto lhs,
    Testable auto rhs,
    std::source_location source_location /* = std::source_location::current() */
)
{
	if constexpr (std::is_enum_v<decltype(lhs)>)
	{
		if (lhs != rhs)
		{
			throw std::runtime_error {
				std::format(
				    "expect_eq: {} == {} @ {}:{}",
				    std::to_underlying<decltype(lhs)>(lhs),
				    std::to_underlying<decltype(rhs)>(rhs),
				    source_location.file_name(),
				    source_location.line()
				),
			};
		}
	}
	// TODO(Light): ensure that rhs type can't cause trouble
	else if constexpr (std::is_pointer_v<decltype(lhs)>)
	{
		if (lhs != rhs)
		{
			throw std::runtime_error {
				std::format(
				    "expect_eq: 0x{:x} == 0x{:x} @ {}:{}",
				    std::bit_cast<size_t>(lhs),
				    std::bit_cast<size_t>(rhs),
				    source_location.file_name(),
				    source_location.line()
				),
			};
		}
	}
	else if (lhs != rhs)
	{
		throw std::runtime_error {
			std::format(
			    "expect_eq: {} == {} @ {}:{}",
			    lhs,
			    rhs,
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

void expect_ne(
    Testable auto lhs,
    Testable auto rhs,
    std::source_location source_location /* = std::source_location::current() */
)
{
	if constexpr (std::is_enum_v<decltype(lhs)>)
	{
		if (lhs != rhs)
		{
			throw std::runtime_error {
				std::format(
				    "expect_ne: {} != {} @ {}:{}",
				    std::to_underlying<decltype(lhs)>(lhs),
				    std::to_underlying<decltype(rhs)>(rhs),
				    source_location.file_name(),
				    source_location.line()
				),
			};
		}
	}
	// TODO(Light): ensure that rhs type can't cause trouble
	else if constexpr (std::is_pointer_v<decltype(lhs)>)
	{
		if (lhs == rhs)
		{
			throw std::runtime_error {
				std::format(
				    "expect_eq: 0x{:x} != 0x{:x} @ {}:{}",
				    std::bit_cast<size_t>(lhs),
				    std::bit_cast<size_t>(rhs),
				    source_location.file_name(),
				    source_location.line()
				),
			};
		}
	}
	else if (lhs == rhs)
	{
		throw std::runtime_error {
			std::format(
			    "expect_ne: {} != {} @ {}:{}",
			    lhs,
			    rhs,
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

void expect_le(
    Testable auto lhs,
    Testable auto rhs,
    std::source_location source_location /* = std::source_location::current() */
)
{
	if (lhs > rhs)
	{
		throw std::runtime_error {
			std::format(
			    "expect_le: {} <= {} @ {}:{}",
			    lhs,
			    rhs,
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

void expect_ge(
    Testable auto lhs,
    Testable auto rhs,
    std::source_location source_location /* = std::source_location::current() */
)
{
	if (lhs < rhs)
	{
		throw std::runtime_error {
			std::format(
			    "expect_ge: {} >= {} @ {}:{}",
			    lhs,
			    rhs,
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

void expect_true(
    bool expression,
    std::source_location source_location /* = std::source_location::current() */
)
{
	if (!expression)
	{
		throw std::runtime_error {
			std::format(
			    "expect_true: {} @ {}:{}",
			    expression,
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

void expect_false(
    bool expression,
    std::source_location source_location /* = std::source_location::current() */
)
{
	if (expression)
	{
		throw std::runtime_error {
			std::format(
			    "expect_false: {} @ {}:{}",
			    expression,
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

void expect_not_nullptr(
    auto *pointer,
    std::source_location source_location /* = std::source_location::current() */
)
{
	if (pointer == nullptr)
	{
		throw std::runtime_error {
			std::format(
			    "expect_not_nullptr @ {}:{}",
			    source_location.file_name(),
			    source_location.line()
			),
		};
	}
}

void expect_str_contains(
    const std::string &string,
    const std::string &token,
    std::source_location source_location /* = std::source_location::current() */
)
{
	if (!string.contains(token))
	{
		throw std::runtime_error {
			std::format(
			    "expect_str_contains @ {}:{} \nstring: {}\n token: {}",
			    source_location.file_name(),
			    source_location.line(),
			    string,
			    token
			),
		};
	}
}


} // namespace lt::test
