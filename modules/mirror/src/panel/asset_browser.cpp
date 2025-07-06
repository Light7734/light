#include <engine/engine.hpp>
#include <engine/utils/serializer.hpp>
#include <imgui.h>
#include <mirror/panel/asset_browser.hpp>

namespace Light {

AssetBrowserPanel::AssetBrowserPanel(Ref<Scene> activeScene)
    : m_current_directory("Assets")
    , m_assets_path("Assets")
    , m_active_scene(activeScene)
{
	ResourceManager::load_texture("_Assets_Directory", "EngineResources/Icons/Asset_Directory.png");
	ResourceManager::load_texture("_Assets_Scene", "EngineResources/Icons/Asset_Scene.png");
	ResourceManager::load_texture("_Assets_Image", "EngineResources/Icons/Asset_Image.png");
	ResourceManager::load_texture("_Assets_Text", "EngineResources/Icons/Asset_Text.png");

	m_directory_texture = ResourceManager::get_texture("_Assets_Directory");
	m_scene_texture = ResourceManager::get_texture("_Assets_Scene");
	m_image_texture = ResourceManager::get_texture("_Assets_Image");
	m_text_texture = ResourceManager::get_texture("_Assets_Text");
}

void AssetBrowserPanel::on_user_interface_update()
{
	ImGui::Begin("Content Browser");

	// Parent directory button
	if (m_current_directory != std::filesystem::path("Assets"))
	{
		if (ImGui::Button(" <--  "))
		{
			m_current_directory = m_current_directory.parent_path();
		}
	}

	auto regionAvail = ImGui::GetContentRegionAvail();
	auto cellSize = m_file_size + m_file_padding;
	auto columnCount = std::clamp(
	    static_cast<uint32_t>(std::floor(regionAvail.x / cellSize)),
	    1u,
	    64u
	);

	if (ImGui::BeginTable("ContentBrowser", columnCount))
	{
		m_directory_texture->bind(0u);
		for (const auto &dirEntry : std::filesystem::directory_iterator(m_current_directory))
		{
			const auto &path = dirEntry.path();
			auto extension = dirEntry.path().extension().string();

			// TODO: Tidy up
			auto assetType = AssetType {};
			assetType = extension.empty() ? AssetType::Directory :

			            extension == ".txt"  ? AssetType::Text :
			            extension == ".glsl" ? AssetType::Text :

			            extension == ".png" ? AssetType::Image :

			            extension == ".scene" ? AssetType::Scene :

			                                    AssetType::None;

			// Extension not supported
			if (assetType == AssetType::None)
			{
				continue;
			}

			// Button
			ImGui::TableNextColumn();
			ImGui::PushID(path.c_str());
			switch (assetType)
			{
			// Directory
			case AssetType::Directory:
				if (ImGui::ImageButton(
				        m_directory_texture->get_texture(),
				        ImVec2(m_file_size, m_file_size),
				        ImVec2 { 0.0f, 0.0f },
				        ImVec2 { 1.0f, 1.0f },
				        0,
				        ImVec4 { 0.0f, 0.0f, 0.0f, 0.0f },
				        ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f }
				    ))
				{
					m_current_directory /= path.filename();
				}
				break;

			// Scene
			case AssetType::Scene:
				if (ImGui::ImageButton(
				        m_scene_texture->get_texture(),
				        ImVec2(m_file_size, m_file_size),
				        ImVec2 { 0.0f, 0.0f },
				        ImVec2 { 1.0f, 1.0f },
				        0,
				        ImVec4 { 0.0f, 0.0f, 0.0f, 0.0f },
				        ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f }
				    ))
				{
					auto serializer = SceneSerializer { m_active_scene };
					lt_log(info, "Attempting to deserialize: {}", path.string());
					serializer.deserialize(path.string());
				}
				break;

			// Image
			case AssetType::Image:
				if (ImGui::ImageButton(
				        m_image_texture->get_texture(),
				        ImVec2(m_file_size, m_file_size),
				        ImVec2 { 0.0f, 0.0f },
				        ImVec2 { 1.0f, 1.0f },
				        0,
				        ImVec4 { 0.0f, 0.0f, 0.0f, 0.0f },
				        ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f }
				    ))
				{
				}
				break;

			// Text
			case AssetType::Text:
				if (ImGui::ImageButton(
				        m_text_texture->get_texture(),
				        ImVec2(m_file_size, m_file_size),
				        ImVec2 { 0.0f, 0.0f },
				        ImVec2 { 1.0f, 1.0f },
				        0,
				        ImVec4 { 0.0f, 0.0f, 0.0f, 0.0f },
				        ImVec4 { 1.0f, 1.0f, 1.0f, 1.0f }
				    ))
				{
				}
				break;


			default: break;
			}
			// Label
			ImGui::Text("%s", path.filename().c_str());
			ImGui::PopID();
		}

		ImGui::EndTable();
	}
	ImGui::End();
}

} // namespace Light
