export module renderer.vk.device;

import preliminary;
import logger;
import renderer.vk.instance;
import renderer.vk.api_wrapper;
import renderer.vk.gpu;
import renderer.vk.surface;

export namespace lt::renderer::vkb {

class Device
{
public:
	Device(not_null<Gpu *> gpu, not_null<Surface *> surface);

	void wait_idle()
	{
		m_device.wait_idle();
	}

	[[nodiscard]] auto vk() -> vk::Device &
	{
		return m_device;
	}

	[[nodiscard]] auto get_family_indices() const -> std::vector<u32>
	{
		return { m_graphics_queue_family_index, m_present_queue_family_index };
	}

	[[nodiscard]] auto graphics_queue() -> vk::Queue &
	{
		return m_graphics_queue;
	}

	[[nodiscard]] auto present_queue() -> vk::Queue &
	{
		return m_present_queue;
	}

private:
	void initialize_physical_device();

	void initialize_logical_device();

	void initialize_queue_indices();

	[[nodiscard]] auto find_suitable_queue_family() const -> u32;

	vkb::Gpu *m_gpu {};

	vkb::Surface *m_surface {};

	vk::Device m_device;

	vk::Queue m_graphics_queue {};

	vk::Queue m_present_queue {};

	u32 m_graphics_queue_family_index = vk::constants::queue_family_ignored;

	u32 m_present_queue_family_index = vk::constants::queue_family_ignored;
};

} // namespace lt::renderer::vkb

namespace lt::renderer::vkb {

Device::Device(not_null<Gpu *> gpu, not_null<Surface *> surface): m_gpu(gpu), m_surface(surface)
{
	ensure(m_surface->vk(), "Failed to initialize vk::Device: null vulkan surface");

	initialize_queue_indices();
	initialize_logical_device();

	m_graphics_queue = vk::Queue(m_device, m_graphics_queue_family_index, 0u);
	m_present_queue = vk::Queue(m_device, m_present_queue_family_index, 0u);


	if (m_graphics_queue_family_index == m_present_queue_family_index)
	{
		m_device.name(m_present_queue, "graphics|present queue");
	}
	else
	{
		m_device.name(m_graphics_queue, "graphics queue");
		m_device.name(m_present_queue, "present queue");
	}
}

void Device::initialize_logical_device()
{
	m_device = vk::Device(
            m_gpu->vk(),
	    vk::Device::CreateInfo {
	        .queue_indices = std::set { m_graphics_queue_family_index, m_present_queue_family_index },

            .extensions = {
                vk::device_extension_names::swapchain,
                vk::device_extension_names::dynamic_rendering,
                vk::device_extension_names::descriptor_indexing,
            },

            .features = {
                .geometry_shader = true,
                .multi_draw_indirect = true,
                .draw_indirect_first_instance = true,
                .sampler_anisotropy = true,
            },

            .dynamic_rendering_features = m_gpu->vk().get_supported_dynamic_rendering_features(),

            .descriptor_indexing_features = { 
                m_gpu->vk().get_supported_descriptor_indexing_features() 
            },
	    }
	);

	m_device.load_functions();
}

void Device::initialize_queue_indices()
{
	auto properties = m_gpu->vk().get_queue_family_properties();
	for (auto idx = u32 { 0u }; const auto &property : properties)
	{
		if (property.queue_flags & vk::QueueFlags::graphics_bit)
		{
			m_graphics_queue_family_index = idx;
		}

		if (m_gpu->vk().queue_family_supports_surface(m_surface->vk(), idx))
		{
			m_present_queue_family_index = idx;
		}

		if (m_graphics_queue_family_index != vk::constants::queue_family_ignored
		    && m_present_queue_family_index != vk::constants::queue_family_ignored)
		{
			break;
		}

		++idx;
	}

	ensure(
	    m_graphics_queue_family_index != vk::constants::queue_family_ignored,
	    "Failed to find graphics queue family"
	);

	ensure(
	    m_present_queue_family_index != vk::constants::queue_family_ignored,
	    "Failed to find presentation queue family"
	);
}

} // namespace lt::renderer::vkb
