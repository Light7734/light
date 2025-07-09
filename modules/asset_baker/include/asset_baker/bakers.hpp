#pragma once

#include <asset_parser/assets/texture.hpp>
#include <filesystem>
#include <logger/logger.hpp>
#include <string_view>
#include <unordered_set>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace lt {

class Loader
{
public:
	[[nodiscard]] virtual auto get_name() const -> std::string_view = 0;

	Loader() = default;

	Loader(Loader &&) = default;

	Loader(const Loader &) = delete;

	auto operator=(Loader &&) -> Loader & = default;

	auto operator=(const Loader &) -> Loader & = delete;

	virtual ~Loader() = default;

private:
};

class TextureLoader: public Loader
{
public:
	TextureLoader() = default;

	[[nodiscard]] virtual auto load(std::filesystem::path file_path) const
	    -> Assets::TextureAsset::PackageData
	    = 0;
};


class StbLoader: public TextureLoader
{
public:
	StbLoader() = default;

	void load(std::filesystem::path path);

	[[nodiscard]] static auto get_supported_extensions() -> std::unordered_set<std::string_view>
	{
		return { ".png" };
	}

	[[nodiscard]] auto get_name() const -> std::string_view override
	{
		return "StbLoader";
	}

	[[nodiscard]] auto load(std::filesystem::path file_path) const
	    -> Assets::TextureAsset::PackageData override
	{
		auto width = int {};
		auto height = int {};
		auto channels = int {};

		auto *pixels = stbi_load(file_path.string().c_str(), &width, &height, &channels, 4);
		if (!pixels)
		{
			throw std::runtime_error {
				std::format("Failed to load image file at: {} using stbi_load", file_path.string()),
			};
		}

		const auto metadata = Assets::Asset::Metadata {
			.type = Assets::Asset::Type::Texture,
		};

		const auto texture_metadata = Assets::TextureAsset::Metadata {
            .format = Assets::TextureAsset::Format::RGBA8,
            .num_components = static_cast<uint32_t>(channels),
            .pixel_size = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height),
                {},
            },
        };

		auto pixels_blob = Assets::Blob {};
		pixels_blob.resize(static_cast<size_t>(width) * height * channels);

		// TODO(Light): figure out if it's possible to directly populate a blob with stbi functions
		memcpy(pixels_blob.data(), pixels, pixels_blob.size());
		stbi_image_free(pixels);

		return Assets::TextureAsset::PackageData {
			.metadata = metadata,
			.texture_metadata = texture_metadata,
			.pixels = std::move(pixels_blob),
		};
	}
};

class TextureLoaderFactory
{
public:
	static auto create(std::string_view file_extension) -> std::unique_ptr<TextureLoader>
	{
		if (StbLoader::get_supported_extensions().contains(file_extension))
		{
			return std::make_unique<StbLoader>();
		}

		return {};
	}
};

} // namespace lt
