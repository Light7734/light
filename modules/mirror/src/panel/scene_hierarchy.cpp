#include <engine/scene/components.hpp>
#include <entt/entt.hpp>
#include <imgui.h>
#include <mirror/panel/properties.hpp>
#include <mirror/panel/scene_hierarchy.hpp>

namespace Light {

SceneHierarchyPanel::SceneHierarchyPanel(): m_context(nullptr), m_properties_panel_context(nullptr)
{
}

SceneHierarchyPanel::SceneHierarchyPanel(Ref<Scene> context, Ref<PropertiesPanel> properties_panel)
    : m_context(std::move(context))
    , m_properties_panel_context(std::move(properties_panel))
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

void SceneHierarchyPanel::set_context(Ref<Scene> context, Ref<PropertiesPanel> properties_panel)
{
	if (properties_panel)
	{
		m_properties_panel_context = std::move(properties_panel);
	}

	m_context = std::move(context);
}

void SceneHierarchyPanel::draw_node(Entity entity, const std::string &label)
{
	auto flags = ImGuiTreeNodeFlags {
		// NOLINTNEXTLINE
		(m_selection_context == entity ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags {})
		| ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth
	};

	// NOLINTNEXTLINE
	const auto expanded = ImGui::TreeNodeEx(
	    std::bit_cast<void *>(static_cast<uint64_t>(entity)),
	    flags,
	    "%s",
	    label.c_str()
	);

	if (ImGui::IsItemClicked())
	{
		m_selection_context = entity;
		m_properties_panel_context->set_entity_context(entity);
	}

	if (expanded)
	{
		ImGui::TextUnformatted("TEST_OPENED_TREE!");
		ImGui::TreePop();
	}
}

} // namespace Light
