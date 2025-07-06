#include <cmath>
#include <engine/math/random.hpp>


namespace Light::Math {

auto rand(int min, int max, int decimals /* = 0 */) -> float
{
	const auto dec = static_cast<int>(std::pow(10, decimals));
	min *= dec;
	max *= dec;

	return (min + (::rand() % (max)-min)) / (float)dec;
}

auto rand_vec2(int min, int max, int decimals /* = 0 */) -> glm::vec2
{
	const auto dec = static_cast<int>(std::pow(10, decimals));
	min *= dec;
	max *= dec;

	auto r1 = (min + (::rand() % (max)-min)) / (float)dec;
	auto r2 = (min + (::rand() % (max)-min)) / (float)dec;

	return { r1, r2 };
}

auto rand_vec3(int min, int max, int decimals /* = 0 */) -> glm::vec3
{
	const auto dec = static_cast<int>(std::pow(10, decimals));
	min *= dec;
	max *= dec;

	auto r1 = (min + (::rand() % (max - min))) / (float)dec;
	auto r2 = (min + (::rand() % (max - min))) / (float)dec;
	auto r3 = (min + (::rand() % (max - min))) / (float)dec;

	return { r1, r2, r3 };
}
} // namespace Light::Math

