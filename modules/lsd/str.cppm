export module lsd.str;
import std;

export namespace lt::lsd {

using c_str = const char *;

using str = std::string;

using str_view = std::string_view;

template<typename... T>
using format_str = std::format_string<T...>;

using std::format_context;
using std::format_parse_context;
using std::format_to;
using std::formatter;

} // namespace lt::lsd
