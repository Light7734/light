#include <memory/scope.hpp>
#include <renderer/backend/vk/messenger.hpp>
#include <renderer/frontend/messenger.hpp>

namespace lt::renderer {

[[nodiscard]] /* static */ auto IMessenger::create(
    Api target_api,
    IInstance *instance,
    CreateInfo info
) -> memory::Scope<IMessenger>
{
	ensure(
	    info.severities != MessageSeverity::none,
	    "Failed to create vk::Messenger: severities == none"
	);

	ensure(info.types != MessageType::none, "Failed to create vk::Messenger: types == none");

	ensure(info.callback, "Failed to create vk::Messenger: null callback");

	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vk::Messenger>(instance, std::move(info));
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}
} // namespace lt::renderer
