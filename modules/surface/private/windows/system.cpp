#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <surface/system.hpp>

namespace lt::surface {

// This class is to ensure glfwInit/glfwTerminate is called only once and exactly when needed during
// entire application runtime
class GlfwSingleton
{
public:
	[[nodiscard]] static auto get() -> GlfwSingleton &
	{
		static auto instance = GlfwSingleton {};
		return instance;
	}

	GlfwSingleton(GlfwSingleton &&) = delete;

	GlfwSingleton(const GlfwSingleton &) = delete;

	auto operator=(GlfwSingleton &&) -> GlfwSingleton & = delete;

	auto operator=(const GlfwSingleton &) -> GlfwSingleton & = delete;

private:
	GlfwSingleton()
	{
		log_inf("Initializing glfw...");
		ensure(glfwInit(), "Failed to initialize 'glfw'");
		log_inf("...Finished");
	}

	~GlfwSingleton()
	{
		log_inf("Terminating glfw...");
		glfwTerminate();
		log_inf("...Finished");
	}
};

void glfw_error_callbac(int32_t code, const char *description)
{
	log_err("GLFW ERROR: {} -> {}", code, description);
}

void handle_event(GLFWwindow *window, const SurfaceComponent::Event &event)
{
	auto &callbacks = *static_cast<std::vector<SurfaceComponent::EventCallback> *>(
	    glfwGetWindowUserPointer(window)
	);

	for (auto &callback : callbacks)
	{
		if (callback(event))
		{
			return;
		}
	}
}

void bind_glfw_events(GLFWwindow *handle)
{
	glfwSetWindowPosCallback(handle, [](GLFWwindow *window, int xpos, int ypos) {
		handle_event(window, MovedEvent { xpos, ypos });
	});

	glfwSetWindowSizeCallback(handle, [](GLFWwindow *window, int width, int height) {
		handle_event(
		    window,
		    ResizedEvent { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }
		);
	});

	glfwSetWindowCloseCallback(handle, [](GLFWwindow *window) {
		handle_event(window, ClosedEvent {});
	});

	glfwSetWindowFocusCallback(handle, [](GLFWwindow *window, int focus) {
		if (focus == GLFW_TRUE)
		{
			handle_event(window, GainFocusEvent {});
		}
		else
		{
			handle_event(window, LostFocusEvent {});
		}
	});

	glfwSetCursorPosCallback(handle, [](GLFWwindow *window, double xpos, double ypos) {
		handle_event(
		    window,
		    MouseMovedEvent { static_cast<float>(xpos), static_cast<float>(ypos) }
		);
	});

	glfwSetMouseButtonCallback(
	    handle,
	    [](GLFWwindow *window, int button, int action, int /*mods*/) {
		    if (action == GLFW_PRESS)
		    {
			    handle_event(window, ButtonPressedEvent { button });
		    }
		    else if (action == GLFW_RELEASE)
		    {
			    handle_event(window, ButtonReleasedEvent { button });
		    }
	    }
	);

	glfwSetScrollCallback(handle, [](GLFWwindow *window, double /*xoffset*/, double yoffset) {
		handle_event(window, WheelScrolledEvent { static_cast<float>(yoffset) });
	});

	glfwSetKeyCallback(
	    handle,
	    [](GLFWwindow *window, int key, int /*scancode*/, int action, int /*mods*/) {
		    if (action == GLFW_PRESS)
		    {
			    handle_event(window, KeyPressedEvent { key });
		    }
		    else if (action == GLFW_RELEASE)
		    {
			    handle_event(window, KeyReleasedEvent { key });
		    }
	    }
	);

	glfwSetCharCallback(handle, [](GLFWwindow *window, unsigned int character) {
		handle_event(window, KeySetCharEvent { character });
	});
}

System::System(Ref<ecs::Registry> registry): m_registry(std::move(registry))
{
	glfwSetErrorCallback(&glfw_error_callbac);

	// will call `glfwInit()` only the first time
	auto &glfw_instance = GlfwSingleton::get();
	ensure(m_registry, "Failed to initialize surface system: null registry");

	ensure(
	    m_registry->view<SurfaceComponent>().size() == 0,
	    "Failed to initialize surface system: registry has surface component(s)"
	);

	m_registry->get_entt_registry()
	    .on_construct<SurfaceComponent>()
	    .connect<&System::on_surface_construct>(this);

	m_registry->get_entt_registry()
	    .on_update<SurfaceComponent>()
	    .connect<&System::on_surface_update>(this);

	m_registry->get_entt_registry()
	    .on_destroy<SurfaceComponent>()
	    .connect<&System::on_surface_destroy>(this);
}

System::~System()
{
	m_registry->get_entt_registry()
	    .on_construct<SurfaceComponent>()
	    .disconnect<&System::on_surface_construct>(this);

	m_registry->get_entt_registry()
	    .on_update<SurfaceComponent>()
	    .connect<&System::on_surface_update>(this);

	m_registry->get_entt_registry()
	    .on_destroy<SurfaceComponent>()
	    .disconnect<&System::on_surface_destroy>(this);


	m_registry->view<SurfaceComponent>().each([&](const entt::entity entity, SurfaceComponent &) {
		m_registry->get_entt_registry().remove<SurfaceComponent>(entity);
	});
}

void System::on_surface_construct(entt::registry &registry, entt::entity entity)
{
	try
	{
		auto &surface = registry.get<SurfaceComponent>(entity);
		ensure_component_sanity(surface);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		surface.m_glfw_handle = glfwCreateWindow(
		    static_cast<int>(surface.get_resolution().x),
		    static_cast<int>(surface.get_resolution().y),
		    surface.get_title().begin(),
		    nullptr,
		    nullptr
		);
		ensure(surface.m_glfw_handle, "Failed to create 'GLFWwindow'");

		glfwSetWindowUserPointer(surface.m_glfw_handle, &surface.m_event_callbacks);
		surface.m_native_handle = glfwGetX11Window(surface.m_glfw_handle);
		bind_glfw_events(surface.m_glfw_handle);
	}
	catch (...)
	{
		registry.remove<SurfaceComponent>(entity);
		throw;
	}
}

void System::on_surface_update(entt::registry &registry, entt::entity entity)
{
	auto &surface = registry.get<SurfaceComponent>(entity);
	glfwSetWindowUserPointer(surface.m_glfw_handle, &surface.m_event_callbacks);
}

void System::on_surface_destroy(entt::registry &registry, entt::entity entity)
{
	auto &surface = registry.get<SurfaceComponent>(entity);

	if (surface.m_glfw_handle)
	{
		glfwDestroyWindow(surface.m_glfw_handle);
	}
}

void System::set_title(ecs::Entity entity, std::string_view new_title)
{
	auto &surface = entity.get_component<SurfaceComponent>();

	surface.m_title = new_title;
	glfwSetWindowTitle(surface.m_glfw_handle, surface.m_title.c_str());
}

auto System::tick() -> bool
{
	m_registry->view<SurfaceComponent>().each([](SurfaceComponent &surface) {
		glfwSwapBuffers(surface.m_glfw_handle);
	});

	glfwPollEvents();
	return false;
}

void System::set_size(ecs::Entity surface_entity, const math::uvec2 &new_size)
{
	auto &surface = surface_entity.get_component<SurfaceComponent>();
	surface.m_resolution = new_size;

	glfwSetWindowSize(
	    surface.m_glfw_handle,
	    static_cast<int>(new_size.x),
	    static_cast<int>(new_size.y)
	);
}

void System::set_v_sync(ecs::Entity surface_entity, bool vsync)
{
	auto &surface = surface_entity.get_component<SurfaceComponent>();
	surface.m_vsync = vsync;

	glfwSwapInterval(vsync);
}

void System::set_visibility(ecs::Entity surface_entity, bool visible)
{
	auto &surface = surface_entity.get_component<SurfaceComponent>();
	surface.m_visible = visible;

	if (visible)
	{
		glfwShowWindow(surface.m_glfw_handle);
	}
	else
	{
		glfwHideWindow(surface.m_glfw_handle);
	}
}

void System::add_event_listener(
    ecs::Entity surface_entity,
    SurfaceComponent::EventCallback callback
)
{
	auto &surface = surface_entity.get_component<SurfaceComponent>();
	surface.m_event_callbacks.emplace_back(std::move(callback));
}

void System::ensure_component_sanity(const SurfaceComponent &component)
{
	auto [width, height] = component.get_resolution();

	ensure(width != 0u, "Received bad values for surface component: width({}) == 0", width);

	ensure(height != 0u, "Received bad values for surface component: height({}) == 0", height);

	ensure(
	    width < SurfaceComponent::max_dimension,
	    "Received bad values for surface component: width({}) > max_dimension({})",
	    width,
	    SurfaceComponent::max_dimension
	);

	ensure(
	    height < SurfaceComponent::max_dimension,
	    "Received bad values for surface component: height({}) > max_dimension({})",
	    height,
	    SurfaceComponent::max_dimension
	);

	ensure(
	    component.get_title().size() < SurfaceComponent::max_title_length,
	    "Received bad values for surface component: title.size({}) > max_title_length({})",
	    component.get_title().size(),
	    SurfaceComponent::max_title_length
	);
}

} // namespace lt::surface

namespace lt {

} // namespace lt
