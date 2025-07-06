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
			ImGui::OpenPopup("Components");

		if (ImGui::BeginPopup("Components"))
		{
			if (ImGui::Selectable(
			        "SpriteRenderer",
			        false,
			        m_entity_context.has_component<SpriteRendererComponent>() ?
			            ImGuiSelectableFlags_Disabled :
			            NULL
			    ))
				m_entity_context.add_component<SpriteRendererComponent>(
				    Light::ResourceManager::get_texture("awesomeface")
				);

			if (ImGui::Selectable(
			        "Camera",
			        false,
			        m_entity_context.has_component<CameraComponent>() ?
			            ImGuiSelectableFlags_Disabled :
			            NULL
			    ))
				m_entity_context.add_component<CameraComponent>();

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

			    auto projectionType = camera.get_projection_type();
			    auto projectionTypesString = std::array<const char *, 2> {
				    "Orthographic",
				    "Perspective",
			    };

			    if (ImGui::BeginCombo("ProjectionType", projectionTypesString[(int)projectionType]))
			    {
				    for (int i = 0; i < 2; i++)
				    {
					    const auto isSelected = (int)projectionType == i;
					    if (ImGui::Selectable(projectionTypesString[i], isSelected))
					    {
						    projectionType = (SceneCamera::ProjectionType)i;
						    camera.set_projection_type(projectionType);
					    }

					    if (isSelected)
						    ImGui::SetItemDefaultFocus();
				    }

				    ImGui::EndCombo();
			    }

			    if (projectionType == SceneCamera::ProjectionType::Orthographic)
			    {
				    auto orthoSize = float {};
				    auto nearPlane = float {};
				    auto farPlane = float {};

				    orthoSize = camera.get_orthographic_size();
				    nearPlane = camera.get_orthographic_near_plane();
				    farPlane = camera.get_orthographic_far_plane();

				    if (ImGui::DragFloat("Orthographic Size", &orthoSize))
					    camera.set_orthographic_size(orthoSize);

				    if (ImGui::DragFloat("Near Plane", &nearPlane))
					    camera.set_orthographic_near_plane(nearPlane);

				    if (ImGui::DragFloat("Far Plane", &farPlane))
					    camera.set_orthographic_far_plane(farPlane);
			    }

			    else // perspective
			    {
				    auto verticalFOV = float {};
				    auto nearPlane = float {};
				    auto farPlane = float {};

				    verticalFOV = glm::degrees(camera.get_perspective_vertical_fov());
				    nearPlane = camera.get_perspective_near_plane();
				    farPlane = camera.get_perspective_far_plane();

				    if (ImGui::DragFloat("Vertical FOV", &verticalFOV))
					    camera.set_perspective_vertical_fov(glm::radians(verticalFOV));

				    if (ImGui::DragFloat("Near Plane", &nearPlane))
					    camera.set_perspective_near_plane(nearPlane);

				    if (ImGui::DragFloat("Far Plane", &farPlane))
					    camera.set_perspective_far_plane(farPlane);
			    }

			    ImGui::Separator();
		    }
		);
	}

	ImGui::End();
}

void PropertiesPanel::set_entity_context(Entity entity)
{
	m_entity_context = entity;
}

void PropertiesPanel::draw_vec3_control(
    const std::string &label,
    glm::vec3 &values,
    float resetValue /*= 0.0f*/,
    float columnWidth /*= 100.0f*/
)
{
	auto &io = ImGui::GetIO();

	auto boldFont = io.Fonts->Fonts[0];

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2 { 0, 0 });

	auto lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	auto buttonSize = ImVec2 { lineHeight + 3.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	ImGui::PushFont(boldFont);
	if (ImGui::Button("X", buttonSize))
		values.x = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, 0.1f);
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Y", buttonSize))
		values.y = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, 0.1f);
	ImGui::PopItemWidth();
	ImGui::SameLine();


	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Z", buttonSize))
		values.z = resetValue;
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
    UIFunction userInterfaceFunction
)
{
	if (!entity.has_component<ComponentType>())
		return;

	auto &component = entity.get_component<ComponentType>();

	auto regionAvail = ImGui::GetContentRegionAvail();

	auto flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth
	             | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap
	             | ImGuiTreeNodeFlags_FramePadding;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4, 4 });
	auto lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImGui::Separator();

	if (ImGui::TreeNodeEx((void *)typeid(ComponentType).hash_code(), flags, name.c_str()))
	{
		ImGui::PopStyleVar();

		ImGui::SameLine(regionAvail.x - lineHeight * .5f);
		if (ImGui::Button("+", { lineHeight, lineHeight }))
			ImGui::OpenPopup("ComponentSettings");

		if (ImGui::BeginPopup("ComponentSettings"))
		{
			if (ImGui::Selectable("Remove component"))
				entity.remove_component<ComponentType>();

			ImGui::EndPopup();
		}

		userInterfaceFunction(component);
		ImGui::TreePop();
	}
	else
		ImGui::PopStyleVar();
}

} // namespace Light
