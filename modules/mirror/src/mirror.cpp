#define LIGHT_ENTRY_POINT

//
#include <mirror/editor_layer.hpp>
#include <window/window.hpp>

//
#include <app/application.hpp>
#include <app/entrypoint.hpp>
#include <app/layer_stack.hpp>

namespace lt {

class Mirror: public Application
{
public:
	Mirror()
	{
		get_window().set_properties(WindowProperties {
		    .title = "Mirror",
		    .size = glm::uvec2(1280u, 720u),
		    .vsync = true,
		});

		get_layer_stack().emplace_layer<EditorLayer>("MirrorLayer");
	}
};

auto create_application() -> Scope<Application>
{
	return create_scope<Mirror>();
}

} // namespace lt
