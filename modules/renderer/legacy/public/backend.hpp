#pragma once

namespace lt::renderer {

class Backend
{
public:
	enum class API : uint8_t
	{
		vulkan,
		directx,
	};

	Backend() = default;

	Backend(Backend &&) = default;

	auto operator=(Backend &&) -> Backend & = default;

	Backend(const Backend &) = delete;

	auto operator=(const Backend &) -> Backend & = delete;

	virtual ~Backend() = default;

	[[nodiscard]] virtual auto get_api() const -> API = 0;
};

} // namespace lt::renderer
