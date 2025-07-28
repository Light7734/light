#pragma once

#include <math/mat4.hpp>

namespace lt::math {

/**
 * let...
 * a = h / w ==> for aspect ratio adjustment
 * f = 1 / tan(fov / 2) ==> for field of view
 *
 * zdiff = zfar-znear
 * A = (zfar / zdiff) - (zfar / zdiff * znear) ==> for normalization
 *
 * given a 3d position vector xyz, we need to do the following operations to achieve
 * perspective projection:
 * x        afx
 * y -->    fy
 * z     Az - Aznear
 *
 * such calculation can be embdedded in a matrix as:
 *     [x]     [y]     [z]    [w]
 *
 *  |  af   |  0    |  0    | 0      |
 *  ----------------------------------
 *  |  0    |  f    |  0    | 0      |
 *  ----------------------------------
 *  |  0    |  0    |  A    | A*znear|
 *  ----------------------------------
 *  |  0    |  0    |  1    | 0      |
 *
 * the 1 at [z][3] is to save the Z axis into the resulting W for perspective division.
 *
 * thanks to pikuma: https://www.youtube.com/watch?v=EqNcqBdrNyI
 */
template<typename T>
constexpr auto perspective(T field_of_view, T aspect_ratio, T z_near, T z_far)
{
	const T half_fov_tan = std::tan(field_of_view / static_cast<T>(2));

	auto result = mat4_impl<T> { T { 0 } };

	result[0][0] = T { 1 } / (aspect_ratio * half_fov_tan);

	result[1][1] = T { 1 } / (half_fov_tan);

	result[2][2] = -(z_far + z_near) / (z_far - z_near);

	result[2][3] = -T { 1 };

	result[3][2] = -(T { 2 } * z_far * z_near) / (z_far - z_near);

	return result;
}

} // namespace lt::math
