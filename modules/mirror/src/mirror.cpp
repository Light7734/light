#define LIGHT_ENTRY_POINT

//
#include <mirror/editor_layer.hpp>

//
#include <engine/engine.hpp>

namespace Light {

class Mirror: public Application
{
public:
	Mirror()
	{
		// Set window properties
		auto properties = WindowProperties {
			.title = "Mirror",
			.size = glm::uvec2(1280u, 720u),
			.vsync = true,
		};

		get_window().set_properties(properties);

		// Attach the sandbox layer
		LayerStack::emplace_layer<EditorLayer>("MirrorLayer");
	}
};

auto create_application() -> Scope<Application>
{
	return create_scope<Mirror>();
}

} // namespace Light
