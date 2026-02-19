export module renderer.vk.swapchain;

import preliminary;
import renderer.vk.api_wrapper;
import renderer.vk.surface;
import renderer.vk.device;
import renderer.vk.instance;
import renderer.vk.gpu;
import renderer.frontend;
import math.vec2;
import memory.null_on_move;
import logger;

export namespace lt::renderer::vkb {

class Swapchain: public ISwapchain
{
public:
	Swapchain(ISurface *surface, IGpu *gpu, IDevice *device);

	[[nodiscard]] auto vk() -> vk::Swapchain &
	{
		return m_swapchain;
	}

	[[nodiscard]] auto get_resolution() const -> math::vec2_u32
	{
		return m_resolution;
	}

	[[nodiscard]] auto get_format() const -> vk::Format
	{
		return m_format;
	}

	[[nodiscard]] auto get_image_count() const -> size_t
	{
		return m_images.size();
	}

	[[nodiscard]] auto get_image_view(u32 idx) -> vk::ImageView &
	{
		return m_image_views[idx];
	}

	[[nodiscard]] auto get_image(u32 idx) -> vk::Image &
	{
		return m_images[idx];
	}

private:
	[[nodiscard]] auto get_optimal_image_count(
	    vk::Surface::Capabilities capabilities,
	    u32 desired_image_count
	) const -> u32;

	Gpu *m_gpu;

	Surface *m_surface {};

	Device *m_device;

	vk::Swapchain m_swapchain;

	std::vector<vk::Image> m_images;

	std::vector<vk::ImageView> m_image_views;

	math::vec2_u32 m_resolution {};

	vk::Format m_format {};
};

} // namespace lt::renderer::vkb

/** @todo(Light): unimplemented in gcc -- is it even right to use a private fragment? */
// module :private;
namespace lt::renderer::vkb {

Swapchain::Swapchain(ISurface *surface, IGpu *gpu, IDevice *device)
    : m_surface(static_cast<Surface *>(surface))
    , m_gpu(static_cast<Gpu *>(gpu))
    , m_device(static_cast<Device *>(device))
{
	auto capabilities = m_gpu->vk().get_surface_capabilities(m_surface->vk());
	const auto formats = m_gpu->vk().get_surface_formats(m_surface->vk());

	// TODO(Light): parameterize
	constexpr auto desired_image_count = u32 { 3u };
	const auto surface_format = formats.front();
	m_format = surface_format.format;

	if (capabilities.current_extent.x == std::numeric_limits<u32>::max())
	{
		log::info(
		    "Vulkan surface capabilities current extent is uint32 max... This indicates that the "
		    "surface size will be determined by the extent of a swapchain targeting the surface."
		);


		// TODO(Light): Take surface extent as swapchain creation argument...
		capabilities.current_extent.x = 800u;
		capabilities.current_extent.y = 600u;
	}

	static auto swapchain_idx = 0u;
	m_swapchain = vk::Swapchain(
	    m_device->vk(),
	    m_surface->vk(),
	    vk::Swapchain::CreateInfo {

	        .format = surface_format.format,
	        .color_space = surface_format.color_space,
	        .extent = capabilities.current_extent,
	        .min_image_count = get_optimal_image_count(capabilities, desired_image_count),
	        .queue_family_indices = m_device->get_family_indices(),
	        .present_mode = vk::Swapchain::PresentMode::mailbox,
	        .pre_transform = capabilities.current_transform,
	        .name = std::format("swapchain {}", swapchain_idx++),
	    }
	);
	m_resolution = capabilities.current_extent;
	m_device->vk().wait_idle();

	m_images = m_swapchain.get_images();
	for (auto idx = 0u; auto &image : m_images)
	{
		m_image_views.emplace_back(
		    vk::ImageView {
		        m_device->vk(),
		        image,
		        vk::ImageView::CreateInfo {
                .type = vk::ImageView::Type::_2d,
                .format = surface_format.format,
                .components = {
                    vk::ImageView::Swizzle::identity,
                    vk::ImageView::Swizzle::identity,
                    vk::ImageView::Swizzle::identity,
                    vk::ImageView::Swizzle::identity,
                },
                .range = {
		            .aspect_flags = vk::Image::AspectFlags::color_bit,
		            .base_mip_level = 0u,
		            .level_count = 1u,
		            .base_array_layer = 0u,
		            .layer_count = 1u,
                },

                .name = std::format("swapchain image view {}", idx++),
		        },
		    }
		);
	}
	m_device->vk().wait_idle();
}

[[nodiscard]] auto Swapchain::get_optimal_image_count(
    vk::Surface::Capabilities capabilities,
    u32 desired_image_count
) const -> u32
{
	const auto min_image_count = capabilities.min_image_count;
	const auto max_image_count = capabilities.max_image_count;

	const auto has_max_limit = max_image_count != 0;

	// Desired image count is in range
	if ((!has_max_limit || max_image_count >= desired_image_count)
	    && min_image_count <= desired_image_count)
	{
		return desired_image_count;
	}

	// Fall-back to 2 if in range
	if (min_image_count <= 2 && max_image_count >= 2)
	{
		return 2;
	}

	// Fall-back to min_image_count
	return min_image_count;
}

} // namespace lt::renderer::vkb
