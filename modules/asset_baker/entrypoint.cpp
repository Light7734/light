import preliminary;
import assets.shader;
import logger;
import bakers;

using lt::assets::ShaderAsset;

auto main(i32 argc, char *argv[]) -> i32
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
		const std::string in_path_str = in_path.generic_string();
		const auto out_path = std::format("{}.asset", in_path_str);

		using enum lt::assets::ShaderAsset::Type;

		if (in_path.extension() == ".vert")
		{
			ShaderAsset::pack(out_path, parse_shader(in_path, vertex));
		}
		else if (in_path.extension() == ".frag")
		{
			ShaderAsset::pack(out_path, parse_shader(in_path, fragment));
		}
	}

	return 0;
}
catch (const std::exception &exp)
{
	lt::log::critical("Terminating due to uncaught exception:");
	lt::log::critical("\texception.what: {}:", exp.what());

	return 1;
}
