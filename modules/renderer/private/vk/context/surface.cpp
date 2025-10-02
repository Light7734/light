#include <renderer/vk/context/surface.hpp>
#include <surface/components.hpp>

namespace lt::renderer::vk {

Surface::Surface(ecs::Entity surface_entity): m_surface_entity(surface_entity)
{
	const auto &component = surface_entity.get<surface::SurfaceComponent>();

	ensure(component.get_native_data().display, "Failed to initialize vk::Surface: null x-display");
	ensure(component.get_native_data().window, "Failed to initialize vk::Surface: null x-window");

	auto create_info = VkXlibSurfaceCreateInfoKHR {
		.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
		.dpy = component.get_native_data().display,
		.window = component.get_native_data().window,
	};

	auto *instance = Instance::get();
	auto result = vk_create_xlib_surface_khr(instance, &create_info, nullptr, &m_surface);
}

Surface::~Surface()
{
	if (Instance::get())
	{
		vk_destroy_surface_khr(Instance::get(), m_surface, nullptr);
	}
}

[[nodiscard]] auto Surface::get_framebuffer_size() const -> VkExtent2D
{
	const auto &[width, height] = //
	    m_surface_entity.get<surface::SurfaceComponent>().get_resolution();

	return {
		.width = width,
		.height = height,
	};
}

} // namespace lt::renderer::vk
