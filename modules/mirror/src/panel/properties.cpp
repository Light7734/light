#include <engine/scene/components.hpp>
#include <engine/utils/resource_manager.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include <mirror/panel/properties.hpp>

namespace Light {

void PropertiesPanel::OnUserInterfaceUpdate()
{
	ImGui::Begin("Properties");

	if (m_EntityContext.IsValid())
	{
		if (m_EntityContext.HasComponent<TagComponent>())
		{
			auto &tagComponent = m_EntityContext.GetComponent<TagComponent>();

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			std::strncpy(buffer, tagComponent.tag.c_str(), sizeof(buffer));

			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
				tagComponent.tag = std::string(buffer);
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
			        m_EntityContext.HasComponent<SpriteRendererComponent>() ?
			            ImGuiSelectableFlags_Disabled :
			            NULL
			    ))
				m_EntityContext.AddComponent<SpriteRendererComponent>(
				    Light::ResourceManager::GetTexture("awesomeface")
				);

			if (ImGui::Selectable(
			        "Camera",
			        false,
			        m_EntityContext.HasComponent<CameraComponent>() ?
			            ImGuiSelectableFlags_Disabled :
			            NULL
			    ))
				m_EntityContext.AddComponent<CameraComponent>();

			ImGui::EndPopup();
		}
		ImGui::PopItemWidth();

		DrawComponent<TransformComponent>(
		    "Transform Component",
		    m_EntityContext,
		    [&](auto &transformComponent) {
			    DrawVec3Control("Translation", transformComponent.translation);
		    }
		);

		DrawComponent<SpriteRendererComponent>(
		    "SpriteRenderer Component",
		    m_EntityContext,
		    [&](auto &spriteRendererComponent) {
			    ImGui::ColorEdit4("Color", &spriteRendererComponent.tint[0]);
		    }
		);

		DrawComponent<CameraComponent>(
		    "Camera Component",
		    m_EntityContext,
		    [&](auto &cameraComponent) {
			    auto &camera = cameraComponent.camera;

			    SceneCamera::ProjectionType projectionType = camera.GetProjectionType();
			    const char *projectionTypesString[] = { "Orthographic", "Perspective" };

			    if (ImGui::BeginCombo("ProjectionType", projectionTypesString[(int)projectionType]))
			    {
				    for (int i = 0; i < 2; i++)
				    {
					    const bool isSelected = (int)projectionType == i;
					    if (ImGui::Selectable(projectionTypesString[i], isSelected))
					    {
						    projectionType = (SceneCamera::ProjectionType)i;
						    camera.SetProjectionType(projectionType);
					    }

					    if (isSelected)
						    ImGui::SetItemDefaultFocus();
				    }

				    ImGui::EndCombo();
			    }

			    if (projectionType == SceneCamera::ProjectionType::Orthographic)
			    {
				    float orthoSize, nearPlane, farPlane;

				    orthoSize = camera.GetOrthographicSize();
				    nearPlane = camera.GetOrthographicNearPlane();
				    farPlane = camera.GetOrthographicFarPlane();

				    if (ImGui::DragFloat("Orthographic Size", &orthoSize))
					    camera.SetOrthographicSize(orthoSize);

				    if (ImGui::DragFloat("Near Plane", &nearPlane))
					    camera.SetOrthographicNearPlane(nearPlane);

				    if (ImGui::DragFloat("Far Plane", &farPlane))
					    camera.SetOrthographicFarPlane(farPlane);
			    }

			    else // perspective
			    {
				    float verticalFOV, nearPlane, farPlane;

				    verticalFOV = glm::degrees(camera.GetPerspectiveVerticalFOV());
				    nearPlane = camera.GetPerspectiveNearPlane();
				    farPlane = camera.GetPerspectiveFarPlane();

				    if (ImGui::DragFloat("Vertical FOV", &verticalFOV))
					    camera.SetPerspectiveVerticalFOV(glm::radians(verticalFOV));

				    if (ImGui::DragFloat("Near Plane", &nearPlane))
					    camera.SetPerspectiveNearPlane(nearPlane);

				    if (ImGui::DragFloat("Far Plane", &farPlane))
					    camera.SetPerspectiveFarPlane(farPlane);
			    }

			    ImGui::Separator();
		    }
		);
	}

	ImGui::End();
}

void PropertiesPanel::SetEntityContext(Entity entity)
{
	m_EntityContext = entity;
}

void PropertiesPanel::DrawVec3Control(
    const std::string &label,
    glm::vec3 &values,
    float resetValue /*= 0.0f*/,
    float columnWidth /*= 100.0f*/
)
{
	ImGuiIO &io = ImGui::GetIO();

	auto boldFont = io.Fonts->Fonts[0];

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2 { 0, 0 });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

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
void PropertiesPanel::DrawComponent(
    const std::string &name,
    Entity entity,
    UIFunction userInterfaceFunction
)
{
	if (!entity.HasComponent<ComponentType>())
		return;

	auto &component = entity.GetComponent<ComponentType>();

	ImVec2 regionAvail = ImGui::GetContentRegionAvail();

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth
	                           | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap
	                           | ImGuiTreeNodeFlags_FramePadding;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4, 4 });
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
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
				entity.RemoveComponent<ComponentType>();

			ImGui::EndPopup();
		}

		userInterfaceFunction(component);
		ImGui::TreePop();
	}
	else
		ImGui::PopStyleVar();
}

} // namespace Light
