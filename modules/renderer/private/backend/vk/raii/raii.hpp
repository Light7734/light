#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/backend/vk/vulkan.hpp>

namespace lt::renderer::vk::raii {

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class DebugMessenger
{
public:
	DebugMessenger(Instance *instance, VkDebugUtilsMessengerCreateInfoEXT info)
	    : m_instance(instance)
	    , m_object(m_instance->create_messenger(info))
	{
	}

	~DebugMessenger()
	{
		if (!m_instance)
		{
			return;
		}

		m_instance->destroy_messenger(m_object);
	}

private:
	memory::NullOnMove<Instance *> m_instance {};

	VkDebugUtilsMessengerEXT m_object;
};

} // namespace lt::renderer::vk::raii
