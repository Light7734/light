#pragma once

#include <renderer/backend/vk/raii/raii.hpp>
#include <renderer/frontend/data/buffer.hpp>

namespace lt::renderer::vk {

class Buffer: public IBuffer
{
public:
	Buffer(class IDevice *device, class IGpu *gpu, const CreateInfo &info);

	[[nodiscard]] auto map() -> std::span<std::byte> override;

	void unmap() override;

	// TODO(Light): this is to make copying possible.
	// But it should be removed in the future,
	// Right now it's not possible because: buffers can't understand CommandBuffers.
	// And I'm not sure how to properly abstract over command buffers,
	// before using other APIs...
	[[nodiscard]] auto vk()
	{
		return *m_buffer;
	}

	[[nodiscard]] auto get_size() const -> size_t override
	{
		return m_size;
	}

private:
	[[nodiscard]] auto determine_allocation_info(Usage usage) const -> VkMemoryAllocateInfo;

	[[nodiscard]] auto to_native_usage_flags(Usage usage) const -> VkBufferUsageFlags;

	[[nodiscard]] auto to_native_memory_properties(Usage usage) const -> VkMemoryPropertyFlags;


	[[nodiscard]] auto has_correct_memory_type_bit(uint32_t type_bits, uint32_t type_idx) const
	    -> bool;

	[[nodiscard]] auto has_required_memory_properties(
	    uint32_t required_properties,
	    uint32_t property_flags
	) const -> bool;

	Device *m_device {};

	Gpu *m_gpu {};

	raii::Buffer m_buffer;

	raii::Memory m_memory;

	// TODO(Light): should this reflect the allocation size instead?
	size_t m_size {};
};

} // namespace lt::renderer::vk


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
    , m_memory(m_device, m_buffer, determine_allocation_info(info.usage))
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

[[nodiscard]] auto Buffer::determine_allocation_info(Usage usage) const -> VkMemoryAllocateInfo
{
	const auto requirements = m_device->get_memory_requirements(m_buffer);
	auto memory_properties = m_gpu->get_memory_properties();

	const auto required_properties = to_native_memory_properties(usage);
	auto type = 0u;
	for (auto idx = 0; idx < memory_properties.memoryTypeCount; ++idx)
	{
		const auto property_flags = memory_properties.memoryTypes[idx].propertyFlags;
		if (has_correct_memory_type_bit(requirements.memoryTypeBits, idx)
		    && has_required_memory_properties(required_properties, property_flags))

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

[[nodiscard]] auto Buffer::to_native_usage_flags(Usage usage) const -> VkBufferUsageFlags
{
	switch (usage)
	{
	case Usage::vertex: return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

	case Usage::index: return VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

	case Usage::storage:
		return VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;

	case Usage::staging: return VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	}

	std::unreachable();
}

[[nodiscard]] auto Buffer::to_native_memory_properties(Usage usage) const -> VkMemoryPropertyFlags
{
	switch (usage)
	{
	case Usage::vertex:
	case Usage::index:
	case Usage::storage: return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

	case Usage::staging:
		return VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	}

	std::unreachable();
}

[[nodiscard]] auto Buffer::has_correct_memory_type_bit(uint32_t type_bits, uint32_t type_idx) const
    -> bool
{
	return type_bits & (1 << type_idx);
}

[[nodiscard]] auto Buffer::has_required_memory_properties(
    uint32_t required_properties,
    uint32_t property_flags
) const -> bool
{
	return (property_flags & required_properties) == required_properties;
}

} // namespace lt::renderer::vk
