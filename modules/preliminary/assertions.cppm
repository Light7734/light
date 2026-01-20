export module preliminary.assertions;

import preliminary.build_constants;
import std;

///////////////////////////////////////
// ----------* INTERFACE *--------- //
/////////////////////////////////////
/** To be used for ensuring a condition holds true, throws otherwise. */
export template<typename Expression_T, typename... Args_T>
struct ensure
{
	ensure(
	    const Expression_T &expression,
	    std::format_string<Args_T...> fmt,
	    Args_T &&...args,
	    const std::source_location &location = std::source_location::current()
	);
};

/** To be used for costly checks that should be stripped in release builds. */
export template<typename Expression_T, typename... Args_T>
struct debug_check
{
	debug_check(
	    const Expression_T &expression,
	    std::format_string<Args_T...> fmt,
	    Args_T &&...args,
	    const std::source_location &location = std::source_location::current()
	);
};

export template<typename Expression_T, typename... Args_T>
ensure(Expression_T, std::format_string<Args_T...>, Args_T &&...)
    -> ensure<Expression_T, Args_T...>;

export template<typename Expression_T, typename... Args_T>
debug_check(Expression_T, std::format_string<Args_T...>, Args_T &&...)
    -> debug_check<Expression_T, Args_T...>;

///////////////////////////////////////
// * IMPLEMENTATION -- TEMPLATES *  //
/////////////////////////////////////
template<typename Expression_T, typename... Args_T>
ensure<Expression_T, Args_T...>::ensure(
    const Expression_T &expression,
    std::format_string<Args_T...> fmt,
    Args_T &&...args,
    const std::source_location &location
)
{
	if (!static_cast<bool>(expression))
	{
		throw std::runtime_error { std::format(
			"exception: {}\nlocation: {}:{}",
			std::format(fmt, std::forward<Args_T>(args)...),
			location.file_name(),
			location.line()
		) };
	}
}

template<typename Expression_T, typename... Args_T>
debug_check<Expression_T, Args_T...>::debug_check(
    const Expression_T &expression,
    std::format_string<Args_T...> fmt,
    Args_T &&...args,
    const std::source_location &location
)
{
	if constexpr (build_constants::build_type != build_constants::BuildType::debug)
	{
		return;
	}

	if (!static_cast<bool>(expression))
	{
		throw std::runtime_error { std::format(
			"exception: {}\nlocation: {}:{}",
			std::format(fmt, std::forward<Args_T>(args)...),
			location.file_name(),
			location.line()
		) };
	}
}
