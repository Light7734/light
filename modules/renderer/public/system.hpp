#pragma once

#include <app/system.hpp>
#include <ecs/entity.hpp>
#include <ecs/registry.hpp>
#include <memory/reference.hpp>
#include <memory/scope.hpp>
#include <renderer/api.hpp>
#include <renderer/frontend/messenger.hpp>

namespace lt::renderer {

class System: public app::ISystem
{
public:
	/** config.max_frames_in_flight should not be higher than this value. */
	static constexpr auto frames_in_flight_upper_limit = 5u;

	/** config.max_frames_in_flight should not be lower than this value. */
	static constexpr auto frames_in_flight_lower_limit = 1u;

	struct Configuration
	{
		Api target_api;

		uint32_t max_frames_in_flight;
	};

	struct CreateInfo
	{
		Configuration config;

		memory::Ref<ecs::Registry> registry;

		ecs::Entity surface_entity;

		IMessenger::CreateInfo debug_callback_info;
	};

	System(CreateInfo info);

	~System() override;

	System(System &&) = default;

	System(const System &) = delete;

	auto operator=(System &&) -> System & = default;

	auto operator=(const System &) -> System & = delete;

	void on_register() override;

	void on_unregister() override;

	void tick(app::TickInfo tick) override;

	[[nodiscard]] auto get_last_tick_result() const -> const app::TickResult & override
	{
		return m_last_tick_result;
	}

private:
	Api m_api;

	memory::Ref<ecs::Registry> m_registry;

	ecs::Entity m_surface_entity;

	memory::Scope<class IMessenger> m_messenger;

	class IInstance *m_instance;

	memory::Scope<class ISurface> m_surface;

	memory::Scope<class IGpu> m_gpu;

	memory::Scope<class IDevice> m_device;

	memory::Scope<class ISwapchain> m_swapchain;

	memory::Scope<class IRenderer> m_renderer;

	app::TickResult m_last_tick_result {};

	uint32_t m_frame_idx {};

	uint32_t m_max_frames_in_flight {};
};

} // namespace lt::renderer
