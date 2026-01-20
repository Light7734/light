export module renderer.vk.gpu;

import preliminary;
import renderer.vk.api_wrapper;
import logger;
import renderer.frontend;
import renderer.vk.instance;
import memory.null_on_move;

export namespace lt::renderer::vkb {

class Gpu: public IGpu
{
public:
	Gpu(IInstance *instance);

	[[nodiscard]] auto vk() -> vk::Gpu &;

private:
	vk::Gpu m_gpu;

	vk::Gpu::Properties m_properties {};

	vk::Gpu::MemoryProperties m_memory_properties {};

	std::vector<vk::Gpu::QueueFamilyProperties> m_queue_family_properties;
};

} // namespace lt::renderer::vkb


module :private;
namespace lt::renderer::vkb {

Gpu::Gpu(IInstance *instance)
{
	auto gpus = vk::Gpu::enumerate(static_cast<Instance *>(instance)->vk());

	for (auto &gpu : gpus)
	{
		auto properties = gpu.get_properties();
		auto features = gpu.get_features();

		// GPU is dedicated, a great success!
		if (properties.device_type == vk::Gpu::Type::discrete_gpu && features.geometry_shader)
		{
			m_gpu = gpu;
		}
	}

	if (!m_gpu)
	{
		for (auto &gpu : gpus)
		{
			auto properties = gpu.get_properties();
			auto features = gpu.get_features();

			// GPU is integrated, fall back to anything with geometry shader support...
			if (features.geometry_shader)
			{
				m_gpu = gpu;
				log::warn("Using integrated GPU");
			}
		}
	}

	// No suitable GPU is fonud...
	ensure(m_gpu, "Failed to find any suitable Vulkan physical device");

	m_memory_properties = m_gpu.get_memory_properties();
	m_queue_family_properties = m_gpu.get_queue_family_properties();
}

[[nodiscard]] auto Gpu::vk() -> vk::Gpu &
{
	return m_gpu;
}

} // namespace lt::renderer::vkb
