export module lsd.literals;
import lsd.str;
import std;

export namespace lt {

constexpr str_view operator""sv(const char *str, unsigned long len) noexcept
{
	return str_view { str, len };
}

} // namespace lt
