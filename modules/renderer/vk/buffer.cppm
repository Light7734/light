export module renderer.vk.buffer;

import preliminary;
import renderer.vk.device;
import renderer.vk.gpu;
import renderer.vk.api_wrapper;
import renderer.frontend;

export namespace lt::renderer::vkb {

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

	[[nodiscard]] auto vk() -> vk::Buffer &
	{
		return m_buffer;
	}

private:
	[[nodiscard]] auto determine_allocation_info(Usage usage) const -> vk::Memory::AllocateInfo;

	[[nodiscard]] auto to_native_usage_flags(Usage usage) const -> vk::Buffer::UsageFlags;

	[[nodiscard]] auto to_native_memory_properties(Usage usage) const -> vk::Memory::PropertyFlags;


	[[nodiscard]] auto has_correct_memory_type_bit(u32 type_bits, u32 type_idx) const -> bool;

	[[nodiscard]] auto has_required_memory_properties(
	    u32 required_properties,
	    u32 property_flags
	) const -> bool;

	Device *m_device {};

	Gpu *m_gpu {};

	vk::Buffer m_buffer;

	vk::Memory m_memory;

	// TODO(Light): should this reflect the allocation size instead?
	size_t m_size {};
};

} // namespace lt::renderer::vkb

module :private;
namespace lt::renderer::vkb {

Buffer::Buffer(IDevice *device, IGpu *gpu, const CreateInfo &info)
    : m_device(static_cast<Device *>(device))
    , m_gpu(static_cast<Gpu *>(gpu))
    , m_buffer(
          m_device->vk(),
          vk::Buffer::CreateInfo {
              .size = info.size,
              .usage = to_native_usage_flags(info.usage),
              .sharing_mode = vk::SharingMode::exclusive,
          }
      )
    , m_memory(m_device->vk(), m_buffer, determine_allocation_info(info.usage))
    , m_size(info.size)
{
}

[[nodiscard]] auto Buffer::map() -> std::span<std::byte> /* override */
{
	return m_memory.map(m_size, 0ul);
}

void Buffer::unmap() /* override */
{
	m_memory.unmap();
}

[[nodiscard]] auto Buffer::determine_allocation_info(Usage usage) const -> vk::Memory::AllocateInfo
{
	const auto requirements = m_buffer.get_memory_requirements();
	auto memory_properties = m_gpu->vk().get_memory_properties();

	const auto required_properties = to_native_memory_properties(usage);
	auto type = 0u;
	for (auto idx = 0; const auto &memory_type : memory_properties.memory_types)
	{
		const auto property_flags = memory_type.property_flags;
		if (has_correct_memory_type_bit(requirements.memory_type_bits, idx)
		    && has_required_memory_properties(required_properties, property_flags))

		{
			type = idx;
			break;
		}

		++idx;
	}

	return vk::Memory::AllocateInfo {
		.size = requirements.size,
		.memory_type_idx = type,
	};
}

[[nodiscard]] auto Buffer::to_native_usage_flags(Usage usage) const -> vk::Buffer::UsageFlags
{
	using Flags = vk::Buffer::UsageFlags;
	using enum vk::Buffer::UsageFlags;

	switch (usage)
	{
	case Usage::vertex: return static_cast<Flags>(vertex_buffer_bit | transfer_dst_bit);
	case Usage::index: return static_cast<Flags>(index_buffer_bit | transfer_dst_bit);
	case Usage::storage: return static_cast<Flags>(transfer_dst_bit | storage_buffer_bit);
	case Usage::staging: return transfer_src_bit;
	}

	std::unreachable();
}

[[nodiscard]] auto Buffer::to_native_memory_properties(Usage usage) const
    -> vk::Memory::PropertyFlags
{
	using Flags = vk::Memory::PropertyFlags;
	using enum vk::Memory::PropertyFlags;
	switch (usage)
	{
	case Usage::vertex:
	case Usage::index:
	case Usage::storage: return device_local_bit;
	case Usage::staging: return static_cast<Flags>(host_visible_bit | host_coherent_bit);
	}

	std::unreachable();
}

[[nodiscard]] auto Buffer::has_correct_memory_type_bit(u32 type_bits, u32 type_idx) const -> bool
{
	return type_bits & (1 << type_idx);
}

[[nodiscard]] auto Buffer::has_required_memory_properties(
    u32 required_properties,
    u32 property_flags
) const -> bool
{
	return (property_flags & required_properties) == required_properties;
}

} // namespace lt::renderer::vkb
