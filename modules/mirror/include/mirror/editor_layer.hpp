#pragma once

#include <engine/engine.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <mirror/panel/asset_browser.hpp>
#include <mirror/panel/properties.hpp>
#include <mirror/panel/scene_hierarchy.hpp>

namespace Light {

class EditorLayer: public Layer
{
private:
	std::string m_SceneDir;

	// #todo: add camera controller class to the engine
	glm::vec2 m_Direction;
	float m_Speed = 1000.0f;

	Ref<Scene> m_Scene;

	Ref<SceneHierarchyPanel> m_SceneHierarchyPanel;
	Ref<PropertiesPanel> m_PropertiesPanel;
	Ref<AssetBrowserPanel> m_ContentBrowserPanel;

	Ref<Framebuffer> m_Framebuffer;

	Entity m_CameraEntity;

	ImVec2 m_AvailableContentRegionPrev;

public:
	EditorLayer(const std::string &name);
	~EditorLayer();

	void OnUpdate(float deltaTime) override;

	void OnRender() override;

	void OnUserInterfaceUpdate() override;
};

} // namespace Light
