#include <engine/scene/components.hpp>
#include <engine/utils/resource_manager.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include <mirror/panel/properties.hpp>

namespace Light {

void PropertiesPanel::on_user_interface_update()
{
	ImGui::Begin("Properties");

	if (m_entity_context.is_valid())
	{
		if (m_entity_context.has_component<TagComponent>())
		{
			auto &tagComponent = m_entity_context.get_component<TagComponent>();

			auto buffer = std::array<char, 256> {};
			memset(buffer.data(), 0, buffer.size());
			std::strncpy(buffer.data(), tagComponent.tag.c_str(), buffer.size());

			if (ImGui::InputText("##Tag", buffer.data(), buffer.size()))
			{
				tagComponent.tag = buffer.data();
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add component"))
		{
			ImGui::OpenPopup("Components");
		}

		if (ImGui::BeginPopup("Components"))
		{
			if (ImGui::Selectable(
			        "SpriteRenderer",
			        false,
			        m_entity_context.has_component<SpriteRendererComponent>() ?
			            ImGuiSelectableFlags_Disabled :
			            ImGuiSelectableFlags {}
			    ))
			{
				m_entity_context.add_component<SpriteRendererComponent>(
				    Light::ResourceManager::get_texture("awesomeface")
				);
			}

			if (ImGui::Selectable(
			        "Camera",
			        false,
			        m_entity_context.has_component<CameraComponent>() ?
			            ImGuiSelectableFlags_Disabled :
			            ImGuiSelectableFlags {}
			    ))
			{
				m_entity_context.add_component<CameraComponent>();
			}

			ImGui::EndPopup();
		}
		ImGui::PopItemWidth();

		draw_component<TransformComponent>(
		    "Transform Component",
		    m_entity_context,
		    [&](auto &transformComponent) {
			    draw_vec3_control("Translation", transformComponent.translation);
		    }
		);

		draw_component<SpriteRendererComponent>(
		    "SpriteRenderer Component",
		    m_entity_context,
		    [&](auto &spriteRendererComponent) {
			    ImGui::ColorEdit4("Color", &spriteRendererComponent.tint[0]);
		    }
		);

		draw_component<CameraComponent>(
		    "Camera Component",
		    m_entity_context,
		    [&](auto &cameraComponent) {
			    auto &camera = cameraComponent.camera;

			    auto projection_type = camera.get_projection_type();
			    auto projection_types_str = std::array<const char *, 2> {
				    "Orthographic",
				    "Perspective",
			    };

			    if (ImGui::BeginCombo("ProjectionType", projection_types_str[(int)projection_type]))
			    {
				    for (auto idx = 0; idx < 2; idx++)
				    {
					    const auto is_selected = static_cast<int>(projection_type) == idx;
					    if (ImGui::Selectable(projection_types_str[idx], is_selected))
					    {
						    projection_type = static_cast<SceneCamera::ProjectionType>(idx);
						    camera.set_projection_type(projection_type);
					    }

					    if (is_selected)
					    {
						    ImGui::SetItemDefaultFocus();
					    }
				    }

				    ImGui::EndCombo();
			    }

			    if (projection_type == SceneCamera::ProjectionType::Orthographic)
			    {
				    auto ortho_size = float {};
				    auto near_plane = float {};
				    auto far_plane = float {};

				    ortho_size = camera.get_orthographic_size();
				    near_plane = camera.get_orthographic_near_plane();
				    far_plane = camera.get_orthographic_far_plane();

				    if (ImGui::DragFloat("Orthographic Size", &ortho_size))
				    {
					    camera.set_orthographic_size(ortho_size);
				    }

				    if (ImGui::DragFloat("Near Plane", &near_plane))
				    {
					    camera.set_orthographic_near_plane(near_plane);
				    }

				    if (ImGui::DragFloat("Far Plane", &far_plane))
				    {
					    camera.set_orthographic_far_plane(far_plane);
				    }
			    }

			    else // perspective
			    {
				    auto vertical_fov = float {};
				    auto near_plane = float {};
				    auto far_plane = float {};

				    vertical_fov = glm::degrees(camera.get_perspective_vertical_fov());
				    near_plane = camera.get_perspective_near_plane();
				    far_plane = camera.get_perspective_far_plane();

				    if (ImGui::DragFloat("Vertical FOV", &vertical_fov))
				    {
					    camera.set_perspective_vertical_fov(glm::radians(vertical_fov));
				    }

				    if (ImGui::DragFloat("Near Plane", &near_plane))
				    {
					    camera.set_perspective_near_plane(near_plane);
				    }

				    if (ImGui::DragFloat("Far Plane", &far_plane))
				    {
					    camera.set_perspective_far_plane(far_plane);
				    }
			    }

			    ImGui::Separator();
		    }
		);
	}

	ImGui::End();
}

void PropertiesPanel::set_entity_context(const Entity &entity)
{
	m_entity_context = entity;
}

void PropertiesPanel::draw_vec3_control(
    const std::string &label,
    glm::vec3 &values,
    float reset_value,
    float column_width
)
{
	auto &io = ImGui::GetIO();

	auto *bold_font = io.Fonts->Fonts[0];

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, column_width);
	ImGui::TextUnformatted(label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2 { 0, 0 });

	auto line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	auto button_size = ImVec2 { line_height + 3.0f, line_height };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	ImGui::PushFont(bold_font);
	if (ImGui::Button("X", button_size))
	{
		values.x = reset_value;
	}
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, 0.1f);
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	ImGui::PushFont(bold_font);
	if (ImGui::Button("Y", button_size))
	{
		values.y = reset_value;
	}
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, 0.1f);
	ImGui::PopItemWidth();
	ImGui::SameLine();


	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
	ImGui::PushFont(bold_font);
	if (ImGui::Button("Z", button_size))
	{
		values.z = reset_value;
	}
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &values.z, 0.1f);
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();
	ImGui::Columns(1);
}


template<typename ComponentType, typename UIFunction>
void PropertiesPanel::draw_component(
    const std::string &name,
    Entity entity,
    UIFunction user_interface_function
)
{
	if (!entity.has_component<ComponentType>())
	{
		return;
	}

	auto &component = entity.get_component<ComponentType>();

	auto available_region = ImGui::GetContentRegionAvail();

	// NOLINTNEXTLINE
	auto flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth
	             | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap
	             | ImGuiTreeNodeFlags_FramePadding;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4, 4 });
	auto lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImGui::Separator();

	// NOLINTNEXTLINE
	if (ImGui::TreeNodeEx((void *)typeid(ComponentType).hash_code(), flags, name.c_str()))
	{
		ImGui::PopStyleVar();

		ImGui::SameLine(available_region.x - lineHeight * .5f);
		if (ImGui::Button("+", { lineHeight, lineHeight }))
		{
			ImGui::OpenPopup("ComponentSettings");
		}

		if (ImGui::BeginPopup("ComponentSettings"))
		{
			if (ImGui::Selectable("Remove component"))
			{
				entity.remove_component<ComponentType>();
			}

			ImGui::EndPopup();
		}

		user_interface_function(component);
		ImGui::TreePop();
	}
	else
	{
		ImGui::PopStyleVar();
	}
}

} // namespace Light
