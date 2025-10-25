#include <renderer/backend/vk/context/device.hpp>
#include <renderer/backend/vk/context/gpu.hpp>
#include <renderer/backend/vk/data/buffer.hpp>

namespace lt::renderer::vk {

Buffer::Buffer(IDevice *device, IGpu *gpu, const CreateInfo &info)
    : m_device(static_cast<Device *>(device))
    , m_gpu(static_cast<Gpu *>(gpu))
    , m_buffer(
          m_device,
          VkBufferCreateInfo {
              .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
              .size = info.size,
              .usage = to_native_usage_flags(info.usage),
              .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
          }
      )
    , m_memory(m_device, m_buffer, allocation_info_from_memory_requirements())
    , m_size(info.size)
{
}

[[nodiscard]] auto Buffer::map() -> std::span<std::byte> /* override */
{
	return m_device->map_memory(m_memory, m_size, 0ul);
}

void Buffer::unmap() /* override */
{
	m_device->unmap_memory(m_memory);
}

[[nodiscard]] auto Buffer::to_native_usage_flags(Usage usage) const -> VkBufferUsageFlags
{
	switch (usage)
	{
	case Usage::vertex: return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	case Usage::index: return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
	}

	std::unreachable();
}

[[nodiscard]] auto Buffer::allocation_info_from_memory_requirements() const -> VkMemoryAllocateInfo
{
	const auto requirements = m_device->get_memory_requirements(m_buffer);
	auto memory_properties = m_gpu->get_memory_properties();

	const auto required_properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
	                                 | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	auto type = 0u;
	for (auto idx = 0; idx < memory_properties.memoryTypeCount; ++idx)
	{
		if ((requirements.memoryTypeBits & (1 << idx))
		    && ((memory_properties.memoryTypes[idx].propertyFlags & required_properties)
		        == required_properties))

		{
			type = idx;
			break;
		}
	}

	return VkMemoryAllocateInfo {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.allocationSize = requirements.size,
		.memoryTypeIndex = type,
	};
}

} // namespace lt::renderer::vk
