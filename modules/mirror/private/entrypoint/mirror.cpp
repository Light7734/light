#include <app/application.hpp>
#include <app/entrypoint.hpp>
#include <app/layer_stack.hpp>
#include <math/vec2.hpp>
#include <mirror/layers/editor_layer.hpp>
#include <window/window.hpp>

namespace lt {

class Mirror: public Application
{
public:
	Mirror()
	{
		get_window().set_properties(
		    Window::Properties {
		        .title = "Mirror",
		        .size = math::uvec2(1280u, 720u),
		        .vsync = true,
		    }
		);

		get_layer_stack().emplace_layer<EditorLayer>("MirrorLayer");
	}
};

auto create_application() -> Scope<Application>
{
	return create_scope<Mirror>();
}

} // namespace lt
