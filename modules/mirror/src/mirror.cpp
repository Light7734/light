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
		Light::WindowProperties properties;
		properties.title = "Mirror";
		properties.size = glm::uvec2(1280u, 720u);
		properties.vsync = true;

		m_window->set_properties(properties);

		// Attach the sandbox layer
		LayerStack::emplace_layer<EditorLayer>(("MirrorLayer"));
	}
};

Application *CreateApplication()
{
	return new Mirror();
}

} // namespace Light
