#pragma once

#include <base/base.hpp>
#include <ecs/scene.hpp>

namespace lt::renderer {

/** The system for putting gore on your display
 *
 * Exclusively operates on components:
 * - RendererComponent
 * - PostEffectsComponent
 * - UserInterfaceComponent
 *
 * Requires read acces on components:
 * - TransformComponent
 */
class System
{
public:
	/** The configurations of this system. */
	struct Properties
	{
	};

	/** The requirements for this system to initialize. */
	struct InitRequirements
	{
		Ref<ecs::Registry> registry;
	};

	/** The requirements for this system to tick. */
	struct TickRequirements
	{
		double delta_time;
	};

	[[nodiscard]] System(InitRequirements requirements);

	System(System &&) = default;

	System(const System &) = delete;

	auto operator=(System &&) -> System & = default;

	auto operator=(const System &) -> System & = delete;

	~System();

	void tick(TickRequirements requirements);

private:
	Ref<ecs::Registry> m_registry;
};

} // namespace lt::renderer
