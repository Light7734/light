export module math.trig;

import preliminary;

export namespace lt::math {

[[nodiscard]] constexpr auto to_radians(f32 degrees) -> f32
{
	return degrees * 0.01745329251994329576923690768489f;
}

[[nodiscard]] constexpr auto to_radians(f64 degrees) -> f64
{
	return degrees * 0.01745329251994329576923690768489;
}

[[nodiscard]] constexpr auto to_degrees(f32 radians) -> f32
{
	return radians * 57.295779513082320876798154814105f;
}

[[nodiscard]] constexpr auto to_degrees(f64 radians) -> f64
{
	return radians * 57.295779513082320876798154814105;
}

} // namespace lt::math
