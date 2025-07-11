#pragma once


#include <ecs/entity.hpp>
#include <ecs/scene.hpp>
#include <mirror/panel/panel.hpp>

namespace lt {

class PropertiesPanel;

class SceneHierarchyPanel: public Panel
{
public:
	SceneHierarchyPanel();

	SceneHierarchyPanel(Ref<Scene> context, Ref<PropertiesPanel> properties_panel = nullptr);

	void on_user_interface_update();

	void set_context(Ref<Scene> context, Ref<PropertiesPanel> properties_panel = nullptr);

private:
	void draw_node(Entity entity, const std::string &label);

	Ref<Scene> m_context;

	Ref<PropertiesPanel> m_properties_panel_context;

	Entity m_selection_context;
};

} // namespace lt
