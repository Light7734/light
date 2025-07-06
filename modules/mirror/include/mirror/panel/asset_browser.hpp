#pragma once

#include <engine/engine.hpp>
#include <filesystem>
#include <mirror/panel/panel.hpp>

namespace Light {

class AssetBrowserPanel: public Panel
{
public:
	AssetBrowserPanel(Ref<Scene> active_scene);

	void on_user_interface_update();

private:
	enum class AssetType
	{
		none = 0,
		scene,
		directory,
		text,
		image,
	};

	std::filesystem::path m_current_directory;

	const std::filesystem::path m_assets_path;

	uint32_t m_file_size = 128u;

	uint32_t m_file_padding = 8u;

	Ref<Scene> m_active_scene;

	Ref<Texture> m_directory_texture;

	Ref<Texture> m_scene_texture;

	Ref<Texture> m_image_texture;

	Ref<Texture> m_text_texture;
};

} // namespace Light
