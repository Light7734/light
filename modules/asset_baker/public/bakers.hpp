#pragma once

#include <asset_parser/assets/text.hpp>
#include <asset_parser/assets/texture.hpp>
#include <filesystem>
#include <logger/logger.hpp>
#include <string_view>
#include <unordered_set>

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

class TextureLoaderFactory
{
public:
	static auto create(std::string_view file_extension) -> std::unique_ptr<TextureLoader>
	{
		return {};
	}
};

class TextLoader: Loader
{
public:
	[[nodiscard]] static auto get_supported_extensions() -> std::unordered_set<std::string_view>
	{
		return { ".glsl", ".txt", ".hlsl" };
	}

	[[nodiscard]] auto get_name() const -> std::string_view override
	{
		return "TextLoader";
	}

	[[nodiscard]] auto load(const std::filesystem::path &file_path) const
	    -> Assets::TextAsset::PackageData
	{
		auto stream = std::ifstream { file_path, std::ios::binary };
		if (!stream.good())
		{
			throw std::runtime_error {
				std::format(
				    "Failed to open ifstream for text loading of file: {}",
				    file_path.string()
				),
			};
		}

		auto file_size = std::filesystem::file_size(file_path);

		auto text_blob = Assets::Blob(file_size);

		stream.read((char *)(text_blob.data()), static_cast<long>(file_size)); // NOLINT

		const auto metadata = Assets::Asset::Metadata {
			.type = Assets::Asset::Type::Text,
		};

		const auto text_metadata = Assets::TextAsset::Metadata {
			.lines = {},
		};

		return Assets::TextAsset::PackageData {
			.metadata = metadata,
			.text_metadata = {},
			.text_blob = std::move(text_blob),
		};
	}
};

class TextLoaderFactory
{
public:
	static auto create(std::string_view file_extension) -> std::unique_ptr<TextLoader>
	{
		if (TextLoader::get_supported_extensions().contains(file_extension))
		{
			return std::make_unique<TextLoader>();
		}

		return {};
	}
};

} // namespace lt
