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
