#include <engine/scene/components.hpp>
#include <entt/entt.hpp>
#include <imgui.h>
#include <mirror/panel/properties.hpp>
#include <mirror/panel/scene_hierarchy.hpp>

namespace Light {

SceneHierarchyPanel::SceneHierarchyPanel()
    : m_context(nullptr)
    , m_properties_panel_context(nullptr)
    , m_selection_context()
{
}

SceneHierarchyPanel::
    SceneHierarchyPanel(Ref<Scene> context, Ref<PropertiesPanel> propertiesPanel /* = nullptr */)
    : m_context(context)
    , m_properties_panel_context(propertiesPanel)
{
}

void SceneHierarchyPanel::on_user_interface_update()
{
	if (m_context)
	{
		ImGui::Begin("Hierarchy");

		for (auto entityID : m_context->m_registry.view<TagComponent>())
		{
			auto entity = Entity {
				static_cast<entt::entity>(entityID),
				m_context.get(),
			};

			const auto &tag = entity.get_component<TagComponent>();
			draw_node(entity, tag);
		};
	}

	ImGui::End();
}

void SceneHierarchyPanel::set_context(Ref<Scene> context, Ref<PropertiesPanel> propertiesPanel)
{
	if (propertiesPanel)
		m_properties_panel_context = propertiesPanel;

	m_context = context;
}

void SceneHierarchyPanel::draw_node(Entity entity, const std::string &label)
{
	auto flags = (m_selection_context == entity ? ImGuiTreeNodeFlags_Selected : NULL)
	             | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;

	const auto expanded = ImGui::TreeNodeEx(
	    (void *)(uint64_t)(uint32_t)(entity),
	    flags,
	    label.c_str()
	);

	if (ImGui::IsItemClicked())
	{
		m_selection_context = entity;
		m_properties_panel_context->set_entity_context(entity);
	}

	if (expanded)
	{
		ImGui::Text("TEST_OPENED_TREE!");
		ImGui::TreePop();
	}
}

} // namespace Light
