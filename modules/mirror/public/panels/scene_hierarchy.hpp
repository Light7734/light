#pragma once

#include <ecs/entity.hpp>
#include <ecs/registry.hpp>
#include <memory/reference.hpp>
#include <mirror/panels/panel.hpp>

namespace lt {

class PropertiesPanel;

class SceneHierarchyPanel: public Panel
{
public:
	SceneHierarchyPanel();

	SceneHierarchyPanel(
	    memory::Ref<Scene> context,
	    memory::Ref<PropertiesPanel> properties_panel = nullptr
	);

	void on_user_interface_update();

	void set_context(
	    memory::Ref<Scene> context,
	    memory::Ref<PropertiesPanel> properties_panel = nullptr
	);

private:
	void draw_node(Entity entity, const std::string &label);

	memory::Ref<Scene> m_context;

	memory::Ref<PropertiesPanel> m_properties_panel_context;

	Entity m_selection_context;
};

} // namespace lt
