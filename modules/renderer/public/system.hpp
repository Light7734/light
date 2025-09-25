#pragma once

#include <app/system.hpp>
#include <ecs/entity.hpp>
#include <renderer/vk/context/context.hpp>

namespace lt::renderer {

class System: app::ISystem
{
public:
	struct CreateInfo
	{
		Ref<ecs::Registry> registry;
		ecs::Entity surface_entity;
		Ref<app::SystemStats> system_stats;
	};

	[[nodiscard]] System(CreateInfo info)
	    : m_registry(std::move(info.registry))
	    , m_stats(info.system_stats)
	    , m_context(info.surface_entity, info.system_stats)
	{
		ensure(m_stats, "Failed to initialize system: null stats");
		ensure(m_registry, "Failed to initialize renderer system: null registry");
	}

	~System() override = default;

	System(System &&) = default;

	System(const System &) = delete;

	auto operator=(System &&) -> System & = default;

	auto operator=(const System &) -> System & = delete;

	void on_register() override
	{
	}

	void on_unregister() override
	{
	}

	void get_validation_state();

	void tick(app::TickInfo tick) override
	{
	}

	[[nodiscard]] auto get_stats() const -> const app::SystemStats &
	{
		return *m_stats;
	}

	[[nodiscard]] auto get_last_tick_result() const -> const app::TickResult & override
	{
		return m_last_tick_result;
	}

private:
	Ref<ecs::Registry> m_registry;

	Ref<app::SystemStats> m_stats;

	vk::Context m_context;

	app::TickResult m_last_tick_result {};
};

} // namespace lt::renderer
