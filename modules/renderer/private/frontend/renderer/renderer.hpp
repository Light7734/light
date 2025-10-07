#pragma once

#include <memory/scope.hpp>
#include <renderer/api.hpp>

namespace lt::renderer {

class IRenderer
{
public:
	static constexpr auto frames_in_flight_upper_limit = 5u;

	static constexpr auto frames_in_flight_lower_limit = 1u;

	enum class DrawResult : uint8_t
	{
		success = 0,
		invalid_swapchain,
		error,
	};

	[[nodiscard]] static auto create(
	    Api target_api,
	    class IDevice *device,
	    class ISwapchain *swapchain,
	    uint32_t max_frames_in_flight
	) -> memory::Scope<IRenderer>;

	IRenderer() = default;

	virtual ~IRenderer() = default;

	IRenderer(IRenderer &&) = default;

	IRenderer(const IRenderer &) = delete;

	auto operator=(IRenderer &&) -> IRenderer & = default;

	auto operator=(const IRenderer &) -> IRenderer & = delete;

	[[nodiscard]] virtual auto draw(uint32_t frame_idx) -> DrawResult = 0;

	virtual void replace_swapchain(class ISwapchain *swapchain) = 0;
};

} // namespace lt::renderer
