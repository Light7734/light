#pragma once

#include <assets/shader.hpp>
#include <logger/logger.hpp>

inline void bake_shader(
    const std::filesystem::path &in_path,
    const std::filesystem::path &out_path,
    lt::assets::ShaderAsset::Type type
)
{
	using lt::assets::ShaderAsset;
	using enum lt::assets::ShaderAsset::Type;

	auto glsl_path = in_path.string();
	auto spv_path = std::format("{}.spv", glsl_path);
	lt::log::trace(
	    "Compiling {} shader {} -> {}",
	    type == vertex ? "vertex" : "fragment",
	    glsl_path,
	    spv_path
	);

	// Don't bother linking to shaderc, just invoke the command with a system call.
	// NOLINTNEXTLINE(concurrency-mt-unsafe)
	system(
	    std::format(
	        "glslc --target-env=vulkan1.4 -std=450core -fshader-stage={} {} -o {}",
	        type == vertex ? "vert" : "frag",
	        glsl_path,
	        spv_path
	    )
	        .c_str()
	);

	auto stream = std::ifstream(spv_path, std::ios::binary);
	lt::ensure(
	    stream.is_open(),
	    "Failed to open compiled {} shader at: {}",
	    type == vertex ? "vert" : "frag",
	    spv_path
	);

	stream.seekg(0, std::ios::end);
	const auto size = stream.tellg();

	auto bytes = std::vector<std::byte>(size);
	stream.seekg(0, std::ios::beg);
	stream.read((char *)bytes.data(), size); // NOLINT
	lt::log::debug("BYTES: {}", bytes.size());
	stream.close();
	std::filesystem::remove(spv_path);

	ShaderAsset::pack(
	    out_path,
	    lt::assets::AssetMetadata {
	        .version = lt::assets::current_version,
	        .type = ShaderAsset::asset_type_identifier,
	    },
	    ShaderAsset::Metadata {
	        .type = type,
	    },
	    std::move(bytes)
	);
}
