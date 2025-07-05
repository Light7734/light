#pragma once

#include <engine/engine.hpp>
#include <filesystem>
#include <mirror/panel/panel.hpp>

namespace Light {

class AssetBrowserPanel: public Panel
{
private:
	enum class AssetType
	{
		None = 0,
		Scene,
		Directory,
		Text,
		Image,
	};

public:
	AssetBrowserPanel(Ref<Scene> activeScene);

	void OnUserInterfaceUpdate();

private:
	std::filesystem::path m_CurrentDirectory;
	const std::filesystem::path m_AssetsPath;

	// TODO: Save configuration
	uint32_t m_FileSize = 128u;
	uint32_t m_FilePadding = 8u;

	Ref<Scene> m_ActiveScene;

	Ref<Texture> m_DirectoryTexture;
	Ref<Texture> m_SceneTexture;
	Ref<Texture> m_ImageTexture;
	Ref<Texture> m_TextTexture;
};

} // namespace Light
