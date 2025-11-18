export module bakers;
import debug.assertions;
import assets.metadata;
import assets.shader;
import logger;
import lsd;

namespace lt {

export void bake_shader(
    const lsd::file::path &in_path,
    const lsd::file::path &out_path,
    assets::ShaderAsset::Type type
)
{
	using assets::ShaderAsset;
	using enum assets::ShaderAsset::Type;

	auto glsl_path = lsd::str { in_path.string() };
	auto spv_path = lsd::format("{}.spv", glsl_path);
	log::trace(
	    "Compiling {} shader {} -> {}",
	    type == vertex ? "vertex" : "fragment",
	    lsd::str { glsl_path },
	    lsd::str { spv_path }
	);

	// Don't bother linking to shaderc, just invoke the command with a system call.
	// NOLINTNEXTLINE(concurrency-mt-unsafe)
	lsd::system(lsd::format(
	                "glslc --target-env=vulkan1.4 -std=450core -fshader-stage={} {} -o {}",
	                type == vertex ? "vert" : "frag",
	                glsl_path,
	                spv_path
	)
	                .c_str());

	auto stream = lsd::file::in_stream(spv_path, lsd::file::ios_binary);
	debug::ensure(
	    stream.is_open(),
	    "Failed to open compiled {} shader at: {}",
	    type == vertex ? "vert" : "frag",
	    spv_path
	);

	stream.seekg(0, lsd::file::ios_end);
	const auto size = stream.tellg();

	auto bytes = lsd::vec<byte>(size);
	stream.seekg(0, lsd::file::ios_beg);
	stream.read((char *)bytes.data(), size); // NOLINT
	log::debug("BYTES: {}", bytes.size());
	stream.close();
	lsd::file::remove(spv_path);

	ShaderAsset::pack(
	    out_path,
	    assets::AssetMetadata {
	        .version = assets::current_version,
	        .type = ShaderAsset::asset_type_identifier,
	    },
	    ShaderAsset::Metadata {
	        .type = type,
	    },
	    lsd::move(bytes)
	);
}

} // namespace lt
