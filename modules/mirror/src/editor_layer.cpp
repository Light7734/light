#include <asset_manager/asset_manager.hpp>
#include <camera/component.hpp>
#include <engine/utils/serializer.hpp>
#include <input/key_codes.hpp>
#include <mirror/editor_layer.hpp>
#include <ui/ui.hpp>

namespace Light {

EditorLayer::EditorLayer(const std::string &name)
    : Layer(name)
    , m_scene_dir("")
    , m_direction { 0.0, 0.0 }
{
	m_scene = create_ref<Scene>();

	m_properties_panel = create_ref<PropertiesPanel>();
	m_sceneHierarchyPanel = create_ref<SceneHierarchyPanel>(m_scene, m_properties_panel);
	m_content_browser_panel = create_ref<AssetBrowserPanel>(m_scene);

	m_framebuffer = Framebuffer::create(
	    {
	        .width = 1,
	        .height = 1,
	        .samples = 1,
	    },
	    GraphicsContext::get_shared_context()
	);

	if (m_scene_dir.empty())
	{
		m_camera_entity = m_scene->create_entity("Camera");
		m_camera_entity.add_component<CameraComponent>(SceneCamera(), true);

		AssetManager::load_texture("Awesomeface", "data/assets/textures/awesomeface.asset");

		auto entity = Entity { m_scene->create_entity("Awesomeface", {}) };
		entity.add_component<SpriteRendererComponent>(
		    AssetManager::get_texture("Awesomeface"),
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

void EditorLayer::on_update(float delta_time)
{
	m_scene->on_update(delta_time);

	if (Input::get_keyboard_key(Key::A))
	{
		m_direction.x = -1.0;
	}
	else if (Input::get_keyboard_key(Key::D))
	{
		m_direction.x = 1.0f;
	}
	else
	{
		m_direction.x = 0.0;
	}

	if (Input::get_keyboard_key(Key::S))
	{
		m_direction.y = -1.0;
	}
	else if (Input::get_keyboard_key(Key::W))
	{
		m_direction.y = 1.0f;
	}
	else
	{
		m_direction.y = 0.0;
	}

	auto &translation = m_camera_entity.get_component<TransformComponent>().translation;
	translation += glm::vec3 { m_direction * m_speed * delta_time, 0.0f };

	if (Input::get_keyboard_key(Key::Escape))
	{
		Application::quit();
	}
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
		auto available_region = ImGui::GetContentRegionAvail();

		if (m_available_content_region_prev != available_region)
		{
			m_framebuffer->resize({ available_region.x, available_region.y });
			auto &camera = m_camera_entity.get_component<CameraComponent>().camera;
			camera.set_viewport_size(
			    static_cast<uint32_t>(available_region.x),
			    static_cast<uint32_t>(available_region.y)
			);

			m_available_content_region_prev = available_region;
		}

		if (GraphicsContext::get_graphics_api() == GraphicsAPI::DirectX)
		{
			ImGui::Image(m_framebuffer->get_color_attachment(), available_region);
		}
		else
		{
			ImGui::Image(
			    m_framebuffer->get_color_attachment(),
			    available_region,
			    ImVec2(0, 1),
			    ImVec2(1, 0)
			);
		}
	}
	ImGui::End();

	// Panels
	m_sceneHierarchyPanel->on_user_interface_update();
	m_properties_panel->on_user_interface_update();
	m_content_browser_panel->on_user_interface_update();

	UserInterface::dockspace_end();
}

} // namespace Light
