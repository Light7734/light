
#include <cstring>
#include <test/test.hpp>

namespace lt::test {

class FuzzDataProvider
{
public:
	FuzzDataProvider(const uint8_t *data, size_t size): m_data(data, size)
	{
	}

	template<typename T>
	    requires(
	        std::is_trivially_constructible_v<T>         //
	        && std::is_trivially_copy_constructible_v<T> //
	        && std::is_trivially_copy_assignable_v<T>
	    )

	auto consume() -> std::optional<T>
	{
		if (m_data.size() < sizeof(T))
		{
			return std::nullopt;
		}

		T value;
		std::memcpy(&value, m_data.data(), sizeof(T));

		m_data = m_data.subspan(sizeof(T));
		return value;
	}

	auto consume_string(size_t size) -> std::optional<std::string>
	{
		if (m_data.size() < size)
		{
			return std::nullopt;
		}

		// NOLINTNEXTLINE
		auto value = std::string { (const char *)m_data.data(), size };
		m_data = m_data.subspan(size);

		return value;
	}

	auto consume_remaining_as_string() -> std::string
	{
		if (m_data.empty())
		{
			return std::string {};
		}

		return { m_data.begin(), m_data.end() };
	};

private:
	std::span<const uint8_t> m_data;
};

} // namespace lt::test

namespace lt::test {

auto process_fuzz_input(const uint8_t *data, size_t size) -> int32_t
try
{
	return details::Registry::process_fuzz_input(data, size);
}
catch (const std::exception &exp)
{
	std::println("Fuzz input resulted in uncaught exception:");
	std::println("\twhat: {}", exp.what());
	std::println("\tinput size: {}", size);

	return EXIT_FAILURE;
}

}; // namespace lt::test

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	return lt::test::process_fuzz_input(data, size);
}
