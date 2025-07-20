#include <asset_baker/bakers.hpp>
#include <asset_parser/assets/text.hpp>
#include <asset_parser/assets/texture.hpp>
#include <asset_parser/parser.hpp>
#include <filesystem>
#include <logger/logger.hpp>

void try_packing_texture(
    const std::filesystem::path &in_path,
    const std::filesystem::path &out_path
)
{
	auto texture_loader = lt::TextureLoaderFactory::create(in_path.extension().string());
	if (!texture_loader)
	{
		// Don't log anything; this is expected.
		return;
	}

	try
	{
		Assets::TextureAsset::pack(texture_loader->load(in_path), out_path);

		log_inf("Packed a texture asset:");
		log_inf("\tloader  : {}", texture_loader->get_name());
		log_inf("\tin  path: {}", in_path.string());
		log_inf("\tout path: {}", out_path.string());
	}
	catch (const std::exception &exp)
	{
		log_err("Failed to pack texture asset:");
		log_err("\tloader  : {}", texture_loader->get_name());
		log_err("\tin path : {}", in_path.string());
		log_err("\tout path: {}", out_path.string());
		log_err("\texp.what: {}", exp.what());
	}
}

void try_packing_text(const std::filesystem::path &in_path, const std::filesystem::path &out_path)
{
	auto text_loader = lt::TextLoaderFactory::create(in_path.extension().string());
	if (!text_loader)
	{
		// Don't log anything; this is expected.
		return;
	}

	try
	{
		Assets::TextAsset::pack(text_loader->load(in_path), out_path);

		log_inf("Packed a text asset:");
		log_inf("\tloader  : {}", text_loader->get_name());
		log_inf("\tin  path: {}", in_path.string());
		log_inf("\tout path: {}", out_path.string());
	}
	catch (const std::exception &exp)
	{
		log_err("Failed to pack a text asset:");
		log_err("\tloader  : {}", text_loader->get_name());
		log_err("\tin path : {}", in_path.string());
		log_err("\tout path: {}", out_path.string());
		log_err("\texp.what: {}", exp.what());
	}
}

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

		auto out_path = in_path;
		out_path.replace_extension(".asset");

		try_packing_texture(in_path, out_path);
		try_packing_text(in_path, out_path);
	}

	return EXIT_SUCCESS;
}
catch (const std::exception &exp)
{
	log_crt("Terminating due to uncaught exception:");
	log_crt("\texception.what: {}:", exp.what());

	return EXIT_FAILURE;
}
