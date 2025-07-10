#include <asset_manager/asset_manager.hpp>
#include <engine/engine.hpp>
#include <engine/utils/serializer.hpp>
#include <imgui.h>
#include <mirror/panel/asset_browser.hpp>

namespace Light {

AssetBrowserPanel::AssetBrowserPanel(Ref<Scene> active_scene)
    : m_current_directory("./data/assets")
    , m_assets_path("./data/assets")
    , m_active_scene(std::move(active_scene))
{
	AssetManager::load_texture("_Assets_Directory", "data/engine/icons/asset/dir.asset");
	AssetManager::load_texture("_Assets_Scene", "data/engine/icons/asset/scene.asset");
	AssetManager::load_texture("_Assets_Image", "data/engine/icons/asset/img.asset");
	AssetManager::load_texture("_Assets_Text", "data/engine/icons/asset/txt.asset");

	m_directory_texture = AssetManager::get_texture("_Assets_Directory");
	m_scene_texture = AssetManager::get_texture("_Assets_Scene");
	m_image_texture = AssetManager::get_texture("_Assets_Image");
	m_text_texture = AssetManager::get_texture("_Assets_Text");
}

void AssetBrowserPanel::on_user_interface_update()
{
	ImGui::Begin("Content Browser");

	// Parent directory button
	if (m_current_directory != std::filesystem::path("data/assets"))
	{
		if (ImGui::Button(" <--  "))
		{
			m_current_directory = m_current_directory.parent_path();
		}
	}

	const auto available_region = ImGui::GetContentRegionAvail();
	const auto cell_size = m_file_size + m_file_padding;
	const auto column_count = std::clamp(
	    static_cast<uint32_t>(std::floor(available_region.x / cell_size)),
	    1u,
	    64u
	);

	if (ImGui::BeginTable("ContentBrowser", static_cast<int>(column_count)))
	{
		m_directory_texture->bind(0u);
		for (const auto &directory_entry : std::filesystem::directory_iterator(m_current_directory))
		{
			const auto &path = directory_entry.path();
			auto extension = directory_entry.path().extension().string();

			auto asset_type = AssetType {};

			if (extension.empty())
			{
				asset_type = AssetType::directory;
			}
			else if (extension == ".txt" || extension == ".glsl")
			{
				asset_type = AssetType::text;
			}
			else if (extension == ".png")
			{
				asset_type = AssetType::image;
			}
			else if (extension == ".scene")
			{
				asset_type = AssetType::scene;
			}
			else
			{
				asset_type = AssetType::none;
			}

			// Extension not supported
			if (asset_type == AssetType::none)
			{
				continue;
			}

			// Button
			ImGui::TableNextColumn();
			ImGui::PushID(path.c_str());
			switch (asset_type)
			{
			// Directory
			case AssetType::directory:
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
			case AssetType::scene:
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
					log_inf("Attempting to deserialize: {}", path.string());
					serializer.deserialize(path.string());
				}
				break;

			// Image
			case AssetType::image:
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
			case AssetType::text:
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
			ImGui::TextUnformatted(fmt::format("{}", path.filename().string()).c_str());
			ImGui::PopID();
		}

		ImGui::EndTable();
	}
	ImGui::End();
}

} // namespace Light
