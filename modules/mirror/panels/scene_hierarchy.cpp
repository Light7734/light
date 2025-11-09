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
#include <ecs/components.hpp>
#include <imgui.h>
#include <memory/reference.hpp>
#include <mirror/panels/properties.hpp>
#include <mirror/panels/scene_hierarchy.hpp>

namespace lt {

SceneHierarchyPanel::SceneHierarchyPanel(): m_context(nullptr), m_properties_panel_context(nullptr)
{
}

SceneHierarchyPanel::SceneHierarchyPanel(
    memory::Ref<Scene> context,
    memory::Ref<PropertiesPanel> properties_panel
)
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

void SceneHierarchyPanel::set_context(
    memory::Ref<Scene> context,
    memory::Ref<PropertiesPanel> properties_panel
)
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

} // namespace lt
