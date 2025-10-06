#pragma once

#include <app/system.hpp>
#include <ecs/entity.hpp>
#include <ecs/registry.hpp>
#include <memory/reference.hpp>
#include <memory/scope.hpp>
#include <renderer/api.hpp>
#include <renderer/components/messenger.hpp>

namespace lt::renderer {

class System: public app::ISystem
{
public:
	struct Configuration
	{
		API target_api;

		uint32_t max_frames_in_flight;
	};

	struct CreateInfo
	{
		Configuration config;

		memory::Ref<ecs::Registry> registry;

		ecs::Entity surface_entity;
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

	void create_messenger_component(ecs::EntityId entity, MessengerComponent::CreateInfo info);

	[[nodiscard]] auto get_last_tick_result() const -> const app::TickResult & override
	{
		return m_last_tick_result;
	}

private:
	API m_api;

	memory::Ref<ecs::Registry> m_registry;

	ecs::Entity m_surface_entity;

	memory::Scope<class IContext> m_context;

	memory::Scope<class IRenderer> m_renderer;

	app::TickResult m_last_tick_result {};

	uint32_t m_frame_idx {};

	uint32_t m_max_frames_in_flight {};
};

} // namespace lt::renderer
