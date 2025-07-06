#define LIGHT_ENTRY_POINT

//
#include <mirror/editor_layer.hpp>

//
#include <engine/engine.hpp>

namespace Light {

class Mirror: public Light::Application
{
public:
	Mirror()
	{
		// Set window properties
		auto properties = Light::WindowProperties {
			.title = "Mirror",
			.size = glm::uvec2(1280u, 720u),
			.vsync = true,
		};

		m_window->set_properties(properties);

		// Attach the sandbox layer
		LayerStack::emplace_layer<EditorLayer>("MirrorLayer");
	}
};

auto create_application() -> Light::Scope<Application>
{
	return Light::create_scope<Mirror>();
}

} // namespace Light
