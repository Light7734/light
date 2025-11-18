export module debug.assertions;

import lsd;

export namespace lt::debug {

template<typename Expression_T, typename... Args_T>
struct ensure
{
	ensure(
	    const Expression_T &expression,
	    lsd::format_str<Args_T...> fmt,
	    Args_T &&...args,
	    const lsd::src_location &location = lsd::src_location::current()
	);
};

template<typename Expression_T, typename... Args_T>
ensure(Expression_T, lsd::format_str<Args_T...>, Args_T &&...) -> ensure<Expression_T, Args_T...>;

template<typename Expression_T, typename... Args_T>
ensure<Expression_T, Args_T...>::ensure(
    const Expression_T &expression,
    lsd::format_str<Args_T...> fmt,
    Args_T &&...args,
    const lsd::src_location &location
)
{
	if (!static_cast<bool>(expression))
	{
		throw lsd::runtime_error { lsd::format(
			"exception: {}\nlocation: {}:{}",
			lsd::format(fmt, lsd::forward<Args_T>(args)...),
			location.file_name(),
			location.line()
		) };
	}
}

} // namespace lt::debug
