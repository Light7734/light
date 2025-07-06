#include <engine/utils/serializer.hpp>
#include <mirror/editor_layer.hpp>

namespace Light {

EditorLayer::EditorLayer(const std::string &name): Layer(name), m_scene_dir("")
{
	m_scene = create_ref<Scene>();

	m_properties_panel = create_ref<PropertiesPanel>();
	m_sceneHierarchyPanel = create_ref<SceneHierarchyPanel>(m_scene, m_properties_panel);
	m_content_browser_panel = create_ref<AssetBrowserPanel>(m_scene);

	m_framebuffer = Framebuffer::create({ 1, 1, 1 }, GraphicsContext::get_shared_context());

	if (m_scene_dir.empty())
	{
		m_camera_entity = m_scene->create_entity("Camera");
		m_camera_entity.add_component<CameraComponent>(SceneCamera(), true);

		ResourceManager::load_texture("Awesomeface", "data/assets/textures/awesomeface.png");

		auto entity = Entity { m_scene->create_entity("Awesomeface", {}) };
		entity.add_component<SpriteRendererComponent>(
		    ResourceManager::get_texture("Awesomeface"),
		    glm::vec4 { 0.0f, 1.0f, 1.0f, 1.0f }
		);
	}
	else
	{
		auto serializer = SceneSerializer { m_scene };
		lt_assert(serializer.deserialize(m_scene_dir), "Failed to de-serialize: {}", m_scene_dir);

		// m_camera_entity = m_scene->GetEntityByTag("Game Camera");
	}
}

EditorLayer::~EditorLayer()
{
	if (!m_scene_dir.empty())
	{
		auto serializer = SceneSerializer { m_scene };
		serializer.serialize(m_scene_dir);
	}
}

void EditorLayer::on_update(float deltaTime)
{
	m_scene->on_update(deltaTime);

	m_direction.x = Input::get_keyboard_key(Key::A) ? -1.0f :
	                Input::get_keyboard_key(Key::D) ? 1.0f :
	                                                  0.0f;

	m_direction.y = Input::get_keyboard_key(Key::S) ? -1.0f :
	                Input::get_keyboard_key(Key::W) ? 1.0f :
	                                                  0.0f;

	auto &cameraTranslation = m_camera_entity.get_component<TransformComponent>().translation;
	cameraTranslation += glm::vec3(m_direction * m_speed * deltaTime, 0.0f);

	if (Input::get_keyboard_key(Key::Escape))
		Application::quit();
}

void EditorLayer::on_render()
{
	m_scene->on_render(m_framebuffer);
}

void EditorLayer::on_user_interface_update()
{
	UserInterface::dockspace_begin();
	ImGui::ShowDemoWindow();

	if (ImGui::Begin("Game"))
	{
		Input::receive_game_events(ImGui::IsWindowFocused());
		auto regionAvail = ImGui::GetContentRegionAvail();

		if (m_available_content_region_prev != regionAvail)
		{
			m_framebuffer->resize({ regionAvail.x, regionAvail.y });
			auto &camera = m_camera_entity.get_component<CameraComponent>().camera;
			camera.set_viewport_size(regionAvail.x, regionAvail.y);

			m_available_content_region_prev = regionAvail;
		}

		if (GraphicsContext::get_graphics_api() == GraphicsAPI::DirectX)
			ImGui::Image(m_framebuffer->get_color_attachment(), regionAvail);
		else
			ImGui::Image(
			    m_framebuffer->get_color_attachment(),
			    regionAvail,
			    ImVec2(0, 1),
			    ImVec2(1, 0)
			);
	}
	ImGui::End();

	// Panels
	m_sceneHierarchyPanel->on_user_interface_update();
	m_properties_panel->on_user_interface_update();
	m_content_browser_panel->on_user_interface_update();

	UserInterface::dockspace_end();
}

} // namespace Light
