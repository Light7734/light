#include <lt_debug/assertions.hpp>
#include <renderer/vk/context/surface.hpp>
#include <surface/components.hpp>

namespace lt::renderer::vk {

Surface::Surface(const ecs::Entity &surface_entity)
{
	const auto &component = surface_entity.get<surface::SurfaceComponent>();

	esnure(component.get_native_data().display, "Failed to initialize usrface: null x-display");
	esnure(component.get_native_data().window, "Failed to initialize usrface: null x-window");

	auto create_info = VkXlibSurfaceCreateInfoKHR {
		.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
		.dpy = component.get_native_data().display,
		.window = component.get_native_data().window,
	};

	auto *instance = Instance::get();
	auto result = vk_create_xlib_surface_khr(instance, &create_info, nullptr, &m_surface);

	const auto &[width, height] = component.get_resolution();
	m_framebuffer_size = {
		.width = width,
		.height = height,
	};
}

Surface::~Surface()
{
	if (Instance::get())
	{
		vk_destroy_surface_khr(Instance::get(), m_surface, nullptr);
	}
}

} // namespace lt::renderer::vk
