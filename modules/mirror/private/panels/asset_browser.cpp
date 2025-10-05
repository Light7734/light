#include <asset_manager/asset_manager.hpp>
#include <ecs/registry.hpp>
#include <ecs/serializer.hpp>
#include <imgui.h>
#include <memory/reference.hpp>
#include <mirror/panels/asset_browser.hpp>
#include <renderer/texture.hpp>

namespace lt {

AssetBrowserPanel::AssetBrowserPanel(memory::Ref<Scene> active_scene)
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
			const auto path_str = path.string();
			ImGui::TableNextColumn();
			ImGui::PushID(path_str.c_str());
			switch (asset_type)
			{
			// Directory
			case AssetType::directory:
				if (ImGui::ImageButton(
				        path_str.c_str(),
				        m_directory_texture->get_texture(),
				        ImVec2(m_file_size, m_file_size)
				    ))
				{
					m_current_directory /= path.filename();
				}
				break;

			// Scene
			case AssetType::scene:
				if (ImGui::ImageButton(
				        path_str.c_str(),
				        m_scene_texture->get_texture(),
				        ImVec2(m_file_size, m_file_size)
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
				        path_str.c_str(),
				        m_image_texture->get_texture(),
				        ImVec2(m_file_size, m_file_size)
				    ))
				{
				}
				break;

			// Text
			case AssetType::text:
				if (ImGui::ImageButton(
				        path_str.c_str(),
				        m_text_texture->get_texture(),
				        ImVec2(m_file_size, m_file_size)
				    ))
				{
				}
				break;


			default: break;
			}
			// Label
			ImGui::TextUnformatted(std::format("{}", path.filename().string()).c_str());
			ImGui::PopID();
		}

		ImGui::EndTable();
	}
	ImGui::End();
}

} // namespace lt
