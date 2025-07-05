#pragma once

#include <engine/engine.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <mirror/panel/asset_browser.hpp>
#include <mirror/panel/properties.hpp>
#include <mirror/panel/scene_hierarchy.hpp>

namespace Light {

class EditorLayer: public Layer
{
public:
	EditorLayer(const std::string &name);

	~EditorLayer();

	void on_update(float deltaTime) override;

	void on_render() override;

	void on_user_interface_update() override;

private:
	std::string m_scene_dir;

	// #todo: add camera controller class to the engine
	glm::vec2 m_direction;

	float m_speed = 1000.0f;

	Ref<Scene> m_scene;

	Ref<SceneHierarchyPanel> m_sceneHierarchyPanel;

	Ref<PropertiesPanel> m_properties_panel;

	Ref<AssetBrowserPanel> m_content_browser_panel;

	Ref<Framebuffer> m_framebuffer;

	Entity m_camera_entity;

	ImVec2 m_available_content_region_prev;
};

} // namespace Light
