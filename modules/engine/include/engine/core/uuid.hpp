#pragma once

#include <random>

namespace Light {

class UUID
{
public:
	UUID(uint64_t uuid = -1);

	operator uint64_t() const
	{
		return m_uuid;
	}

private:
	static std::mt19937_64 s_engine;

	static std::uniform_int_distribution<uint64_t> s_distribution;

	uint64_t m_uuid;
};

} // namespace Light

namespace std {

template<>
struct hash<Light::UUID>
{
	std::size_t operator()(const Light::UUID &uuid) const
	{
		return hash<uint64_t>()(static_cast<uint64_t>(uuid));
	}
};

} // namespace std
