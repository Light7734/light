#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/backend/vk/context/surface.hpp>
#include <surface/components.hpp>

namespace lt::renderer::vk {

Surface::Surface(IInstance *instance, const ecs::Entity &surface_entity)
    : m_surface_entity(surface_entity)
    , m_instance(static_cast<Instance *>(instance))
{
	const auto &component = surface_entity.get<surface::SurfaceComponent>();

	ensure(component.get_native_data().display, "Failed to initialize vk::Surface: null x-display");
	ensure(component.get_native_data().window, "Failed to initialize vk::Surface: null x-window");

	m_surface = m_instance->create_xlib_surface(
	    VkXlibSurfaceCreateInfoKHR {
	        .sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
	        .dpy = component.get_native_data().display,
	        .window = component.get_native_data().window,
	    }
	);
}

Surface::~Surface()
{
	if (!m_instance)
	{
		return;
	}

	m_instance->destroy_surface(m_surface);
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
