#pragma once

#include <app/system.hpp>
#include <ecs/entity.hpp>

namespace lt::renderer {

namespace vk {
class Context;
class Renderer;
class Pass;
class ValidationObserver;
} // namespace vk

class System: public app::ISystem
{
public:
	struct CreateInfo
	{
		Ref<ecs::Registry> registry;

		ecs::Entity surface_entity;

		Ref<app::SystemStats> system_stats;
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


	[[nodiscard]] auto get_stats() const -> const app::SystemStats &
	{
		return *m_stats;
	}

	[[nodiscard]] auto get_last_tick_result() const -> const app::TickResult & override
	{
		return m_last_tick_result;
	}

private:
	class vk::ValidationObserver *m_validation_observer;

	Ref<ecs::Registry> m_registry;

	Ref<app::SystemStats> m_stats;

	Scope<class vk::Context> m_context;

	Ref<class vk::Pass> m_pass;

	Scope<class vk::Renderer> m_renderer;


	app::TickResult m_last_tick_result {};

	uint32_t m_frame_idx {};
};

} // namespace lt::renderer
