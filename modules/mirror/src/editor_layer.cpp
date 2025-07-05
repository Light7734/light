#include <engine/utils/serializer.hpp>
#include <mirror/editor_layer.hpp>

namespace Light {

EditorLayer::EditorLayer(const std::string &name): Layer(name), m_scene_dir("")
{
	m_scene = CreateRef<Scene>();

	m_properties_panel = CreateRef<PropertiesPanel>();
	m_sceneHierarchyPanel = CreateRef<SceneHierarchyPanel>(m_scene, m_properties_panel);
	m_content_browser_panel = CreateRef<AssetBrowserPanel>(m_scene);

	m_framebuffer = Framebuffer::Create({ 1, 1, 1 }, GraphicsContext::GetSharedContext());

	if (m_scene_dir.empty())
	{
		m_camera_entity = m_scene->CreateEntity("Camera");
		m_camera_entity.AddComponent<CameraComponent>(SceneCamera(), true);

		ResourceManager::LoadTexture("Awesomeface", "Assets/Textures/awesomeface.png");
		Entity entity = m_scene->CreateEntity("Awesomeface", {});
		entity.AddComponent<SpriteRendererComponent>(
		    ResourceManager::GetTexture("Awesomeface"),
		    glm::vec4 { 0.0f, 1.0f, 1.0f, 1.0f }
		);
	}
	else
	{
		SceneSerializer serializer(m_scene);
		ASSERT(serializer.Deserialize(m_scene_dir), "Failed to de-serialize: {}", m_scene_dir);

		// m_camera_entity = m_scene->GetEntityByTag("Game Camera");
	}
}

EditorLayer::~EditorLayer()
{
	if (!m_scene_dir.empty())
	{
		SceneSerializer serializer(m_scene);
		serializer.Serialize(m_scene_dir);
	}
}

void EditorLayer::OnUpdate(float deltaTime)
{
	m_scene->OnUpdate(deltaTime);

	m_direction.x = Input::GetKeyboardKey(Key::A) ? -1.0f :
	                Input::GetKeyboardKey(Key::D) ? 1.0f :
	                                                0.0f;

	m_direction.y = Input::GetKeyboardKey(Key::S) ? -1.0f :
	                Input::GetKeyboardKey(Key::W) ? 1.0f :
	                                                0.0f;

	auto &cameraTranslation = m_camera_entity.GetComponent<TransformComponent>().translation;
	cameraTranslation += glm::vec3(m_direction * m_speed * deltaTime, 0.0f);

	if (Input::GetKeyboardKey(Key::Escape))
		Application::Quit();
}

void EditorLayer::OnRender()
{
	m_scene->OnRender(m_framebuffer);
}

void EditorLayer::OnUserInterfaceUpdate()
{
	UserInterface::DockspaceBegin();
	ImGui::ShowDemoWindow();

	if (ImGui::Begin("Game"))
	{
		Input::ReceiveGameEvents(ImGui::IsWindowFocused());
		ImVec2 regionAvail = ImGui::GetContentRegionAvail();

		if (m_available_content_region_prev != regionAvail)
		{
			m_framebuffer->Resize({ regionAvail.x, regionAvail.y });
			auto &camera = m_camera_entity.GetComponent<CameraComponent>().camera;
			camera.SetViewportSize(regionAvail.x, regionAvail.y);

			m_available_content_region_prev = regionAvail;
		}

		if (GraphicsContext::GetGraphicsAPI() == GraphicsAPI::DirectX)
			ImGui::Image(m_framebuffer->GetColorAttachment(), regionAvail);
		else
			ImGui::Image(
			    m_framebuffer->GetColorAttachment(),
			    regionAvail,
			    ImVec2(0, 1),
			    ImVec2(1, 0)
			);
	}
	ImGui::End();

	// Panels
	m_sceneHierarchyPanel->OnUserInterfaceUpdate();
	m_properties_panel->OnUserInterfaceUpdate();
	m_content_browser_panel->OnUserInterfaceUpdate();

	UserInterface::DockspaceEnd();
}

} // namespace Light
