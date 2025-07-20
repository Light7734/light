#pragma once

#include <random>

namespace lt {

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

} // namespace lt

namespace std {

template<>
struct hash<lt::UUID>
{
	std::size_t operator()(const lt::UUID &uuid) const
	{
		return hash<uint64_t>()(static_cast<uint64_t>(uuid));
	}
};

} // namespace std
