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

	[[nodiscard]] auto get_size() const -> size_t override
	{
		return m_size;
	}

private:
	[[nodiscard]] auto to_native_usage_flags(Usage usage) const -> VkBufferUsageFlags;

	[[nodiscard]] auto allocation_info_from_memory_requirements() const -> VkMemoryAllocateInfo;

	Device *m_device {};

	Gpu *m_gpu {};

	raii::Buffer m_buffer;

	raii::Memory m_memory;

	// TODO(Light): should this reflect the allocation size instead?
	size_t m_size {};
};

} // namespace lt::renderer::vk
