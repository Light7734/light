export module math.trig;

export namespace lt::math {

[[nodiscard]] constexpr auto radians(float degrees) -> float
{
	return degrees * 0.01745329251994329576923690768489f;
}

[[nodiscard]] constexpr auto radians(double degrees) -> double
{
	return degrees * 0.01745329251994329576923690768489;
}

[[nodiscard]] constexpr auto degrees(float radians) -> float
{
	return radians * 57.295779513082320876798154814105f;
}

[[nodiscard]] constexpr auto degrees(double radians) -> double
{
	return radians * 57.295779513082320876798154814105;
}


} // namespace lt::math
