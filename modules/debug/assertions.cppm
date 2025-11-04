export module debug.assertions;

import std;

namespace lt::debug {

///////////////////////////////////////
// ----------* INTERFACE *--------- //
/////////////////////////////////////
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

export template<typename Expression_T, typename... Args_T>
ensure(Expression_T, std::format_string<Args_T...>, Args_T &&...)
    -> ensure<Expression_T, Args_T...>;

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

} // namespace lt::debug
