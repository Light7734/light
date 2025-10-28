#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/backend/vk/context/device.hpp>
#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/backend/vk/vulkan.hpp>


namespace lt::renderer::vk::raii {

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

	DebugMessenger(DebugMessenger &&) = default;

	DebugMessenger(const DebugMessenger &) = delete;

	auto operator=(DebugMessenger &&) -> DebugMessenger & = default;

	auto operator=(const DebugMessenger &) -> DebugMessenger & = delete;

private:
	memory::NullOnMove<Instance *> m_instance {};

	VkDebugUtilsMessengerEXT m_object;
};

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

	Buffer(Buffer &&) = default;

	Buffer(const Buffer &) = delete;

	auto operator=(Buffer &&) -> Buffer & = default;

	auto operator=(const Buffer &) -> Buffer & = delete;

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

	Memory(Memory &&) = default;

	Memory(const Memory &) = delete;

	auto operator=(Memory &&) -> Memory & = default;

	auto operator=(const Memory &) -> Memory & = delete;

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


} // namespace lt::renderer::vk::raii
