#pragma once

#include <engine/base/base.hpp>
#include <engine/scene/entity.hpp>
#include <engine/scene/scene.hpp>
#include <mirror/panel/panel.hpp>

namespace Light {

class PropertiesPanel;

class SceneHierarchyPanel: public Panel
{
private:
	Ref<Scene> m_context;
	Ref<PropertiesPanel> m_properties_panel_context;
	Entity m_selection_context;

public:
	SceneHierarchyPanel();
	SceneHierarchyPanel(Ref<Scene> context, Ref<PropertiesPanel> propertiesPanel = nullptr);

	void OnUserInterfaceUpdate();

	void SetContext(Ref<Scene> context, Ref<PropertiesPanel> propertiesPanel = nullptr);

private:
	void DrawNode(Entity entity, const std::string &label);
};

} // namespace Light
