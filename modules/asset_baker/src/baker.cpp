#include <asset_parser/assets/texture.hpp>
#include <asset_parser/parser.hpp>
#include <filesystem>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define ASSERT(x, ...)    \
	if (!(x))             \
	{                     \
		log(__VA_ARGS__); \
		return -1;        \
	}


template<typename... Args>
void log(Args &&...args)
{
	(std::cout << ... << args);
	std::cout << '\n';
}

auto convert_image(const std::filesystem::path &input, const std::filesystem::path &output) -> bool
{
	auto width = int {};
	auto height = int {};
	auto channels = int {};

	auto *pixels = stbi_load(input.string().c_str(), &width, &height, &channels, 4);

	if (!pixels)
		return false;

	auto texture_info = Assets::TextureInfo {
		.size       = static_cast<size_t>(width * height * 4),
		.format     = Assets::TextureFormat::RGBA8,
		.pixel_size = {
		    static_cast<uint32_t>(width),
		    static_cast<uint32_t>(height),
		    0ul,
		},
		.original_file = input.string(),
	};

	auto file = Assets::pack_texture(&texture_info, pixels);

	stbi_image_free(pixels);

	Assets::save_binary_file(output.string().c_str(), file);

	return true;
}

int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false);

	ASSERT(
	    argc == 3,
	    "Argc MUST be 3, 1: execution-path(implicit), 2: input-directory, 3: output-directory"
	);

	for (const auto &p : std::filesystem::directory_iterator(argv[1]))
	{
		if (p.path().extension() == ".png")
		{
			log("Found a texture: ", p);

			auto newp = p.path();
			newp.replace_extension(".asset_texture");
			convert_image(p.path(), newp);
		}
		else if (p.path().extension() == ".obj")
		{
			log("Found a mesh -> ", p, " (unsupported)");
		}
		else
		{
			log("Unknown -> ", p);
		}
	}

	return 0;
}
