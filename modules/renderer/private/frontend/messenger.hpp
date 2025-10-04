#pragma once

#include <ecs/entity.hpp>
#include <renderer/api.hpp>

namespace lt::renderer {

class IMessenger
{
public:
	[[nodiscard]] static auto create(API target_api, class IInstance *instance, ecs::Entity entity)
	    -> Scope<IMessenger>;

	IMessenger() = default;

	virtual ~IMessenger() = default;

	IMessenger(IMessenger &&) = default;

	IMessenger(const IMessenger &) = delete;

	auto operator=(IMessenger &&) -> IMessenger & = default;

	auto operator=(const IMessenger &) -> IMessenger & = delete;
};

} // namespace lt::renderer
