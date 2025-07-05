#include "SceneHierarchyPanel.hpp"

#include "PropertiesPanel.hpp"
#include "Scene/Components.hpp"

#include <entt/entt.hpp>
#include <imgui.h>

namespace Light {

SceneHierarchyPanel::SceneHierarchyPanel()
    : m_Context(nullptr), m_PropertiesPanelContext(nullptr), m_SelectionContext()
{
}

SceneHierarchyPanel::SceneHierarchyPanel(Ref<Scene> context, Ref<PropertiesPanel> propertiesPanel /* = nullptr */)
    : m_Context(context), m_PropertiesPanelContext(propertiesPanel)
{
}

void SceneHierarchyPanel::OnUserInterfaceUpdate()
{
	if (m_Context)
	{
		ImGui::Begin("Hierarchy");

		for (auto entityID : m_Context->m_Registry.view<TagComponent>())
		{
			Entity entity(static_cast<entt::entity>(entityID), m_Context.get());
			const std::string& tag = entity.GetComponent<TagComponent>();

			DrawNode(entity, tag);
		};
	}

	ImGui::End();
}

void SceneHierarchyPanel::SetContext(Ref<Scene> context, Ref<PropertiesPanel> propertiesPanel /* = nullptr */)
{
	if (propertiesPanel)
		m_PropertiesPanelContext = propertiesPanel;

	m_Context = context;
}

void SceneHierarchyPanel::DrawNode(Entity entity, const std::string& label)
{
	ImGuiTreeNodeFlags flags = (m_SelectionContext == entity ? ImGuiTreeNodeFlags_Selected : NULL) |
	                           ImGuiTreeNodeFlags_OpenOnArrow |
	                           ImGuiTreeNodeFlags_SpanFullWidth;

	bool expanded = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity), flags, label.c_str());

	if (ImGui::IsItemClicked())
	{
		m_SelectionContext = entity;
		m_PropertiesPanelContext->SetEntityContext(entity);
	}

	if (expanded)
	{
		ImGui::Text("TEST_OPENED_TREE!");
		ImGui::TreePop();
	}
}

} // namespace Light
