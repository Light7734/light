#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/backend/vk/context/device.hpp>
#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/backend/vk/vulkan.hpp>


namespace lt::renderer::vk::raii { // NOLINTBEGIN(cppcoreguidelines-special-member-functions)

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
		if (m_instance)
		{
			m_instance->destroy_messenger(m_object);
		}
	}

private:
	memory::NullOnMove<Instance *> m_instance {};

	VkDebugUtilsMessengerEXT m_object;
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class Buffer
{
public:
	Buffer(Device *device, VkBufferCreateInfo info)
	    : m_device(device)
	    , m_object(m_device->create_buffer(info))
	{
	}

	~Buffer()
	{
		if (m_device)
		{
			m_device->destroy_buffer(m_object);
		}
	}

	[[nodiscard]] auto operator*() const -> VkBuffer
	{
		return m_object;
	}

	[[nodiscard]] operator VkBuffer() const
	{
		return m_object;
	}

private:
	memory::NullOnMove<Device *> m_device {};

	VkBuffer m_object;
};

class Memory
{
public:
	Memory(Device *device, VkBuffer buffer, VkMemoryAllocateInfo info)
	    : m_device(device)
	    , m_object(m_device->allocate_memory(info))
	{
		m_device->bind_memory(buffer, m_object);
	}

	~Memory()
	{
		if (m_device)
		{
			m_device->free_memory(m_object);
		}
	}

	[[nodiscard]] auto operator*() const -> VkDeviceMemory
	{
		return m_object;
	}

	[[nodiscard]] operator VkDeviceMemory() const
	{
		return m_object;
	}

private:
	memory::NullOnMove<Device *> m_device {};

	VkDeviceMemory m_object = VK_NULL_HANDLE;
};


// NOLINTEND(cppcoreguidelines-special-member-functions)
} // namespace lt::renderer::vk::raii
