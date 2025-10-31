#include <asset_baker/bakers.hpp>
#include <assets/shader.hpp>
#include <logger/logger.hpp>

auto main(int argc, char *argv[]) -> int32_t
try
{
	if (argc != 2)
	{
		throw std::logic_error("Argc should be 2 -- exe dir (implicit) and target dir");
	}

	for (const auto &directory_iterator :
	     std::filesystem::recursive_directory_iterator(argv[1])) // NOLINT
	{
		if (directory_iterator.is_directory())
		{
			continue;
		}

		const auto &in_path = directory_iterator.path();
		const auto out_path = std::format("{}.asset", in_path.c_str());

		if (in_path.extension() == ".vert")
		{
			bake_shader(in_path, out_path, lt::assets::ShaderAsset::Type::vertex);
		}
		else if (in_path.extension() == ".frag")
		{
			bake_shader(in_path, out_path, lt::assets::ShaderAsset::Type::fragment);
		}
	}

	return EXIT_SUCCESS;
}
catch (const std::exception &exp)
{
	lt::log::critical("Terminating due to uncaught exception:");
	lt::log::critical("\texception.what: {}:", exp.what());

	return EXIT_FAILURE;
}
