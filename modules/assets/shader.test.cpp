import test;
import assets.metadata;
import assets.shader;

using ::lt::assets::AssetMetadata;
using ::lt::assets::Blob;
using ::lt::assets::BlobMetadata;
using ::lt::assets::ShaderAsset;

const auto test_data_path = std::filesystem::path { "./data/test_assets" };
const auto tmp_path = std::filesystem::path { "/tmp/lt_assets_tests/" };

[[nodiscard]] auto generate_blob(size_t size) -> Blob
{
	auto blob = Blob {};
	for (auto idx : std::views::iota(0u, size))
	{
		blob.emplace_back(static_cast<byte>(idx));
	}

	return blob;
}

Suite raii = "shader_raii"_suite = [] {
	std::filesystem::current_path(test_data_path);
	std::filesystem::create_directories(tmp_path);

	Case { "happy paths" } = [] {
		auto shader_asset = ShaderAsset { "triangle.frag.asset" };
	};

	Case { "unhappy paths" } = [] {
		// non-existent file
		expect_throw([] { ShaderAsset { "path" }; });

		// incompatible type
		expect_throw([] { ShaderAsset { "dummytext" }; });

		// some random stressing
		expect_throw([] {
			for (auto idx : std::views::iota(0u, 1'000u))
			{
				auto shader_asset = ShaderAsset { std::to_string(idx) };
			}
		});
	};

	Case { "many" } = [] {
		for (auto idx : std::views::iota(0u, 1'000u))
		{
			ignore = idx;
			auto shader_asset = ShaderAsset { "triangle.frag.asset" };
		}
	};
};

// NOLINTNEXTLINE(cppcoreguidelines-interfaces-global-init)
Suite packing = "shader_pack"_suite = [] {
	Case { "Unpacking packed data returns the same data" } = [] {
		const auto out_path = tmp_path / "shader_packing";
		constexpr auto blob_size = size_t { 255u };

		auto blob = generate_blob(blob_size);

		const auto expected_size =                    //
		    sizeof(AssetMetadata::type)               // NOLINT(bugprone-sizeof-container)
		    + sizeof(AssetMetadata::version)          //
		    + sizeof(ShaderAsset::Metadata::type)     //
		    + sizeof(BlobMetadata::tag)               //
		    + sizeof(BlobMetadata::offset)            //
		    + sizeof(BlobMetadata::compression_type)  //
		    + sizeof(BlobMetadata::compressed_size)   //
		    + sizeof(BlobMetadata::uncompressed_size) //
		    + blob.size();

		ShaderAsset::pack(
		    out_path,
		    ShaderAsset::PackData {
		        .asset_metadata = lt::assets::AssetMetadata {
		            .version = lt::assets::current_version,
		            .type = ShaderAsset::asset_type_identifier,
		        },
		        .metadata = ShaderAsset::Metadata {
		            .type = ShaderAsset::Type::vertex,
		        },
		        .code_blob= std::move(blob),
		    }
		);

		auto stream = std::ifstream {
			out_path,
			std::ios::binary,
		};
		expect_true(stream.is_open());

		stream.seekg(0u, std::ios::end);
		const auto file_size = static_cast<size_t>(stream.tellg());
		expect_eq(file_size, expected_size);
		stream.close();

		auto shader_asset = ShaderAsset { out_path };

		const auto &asset_metadata = shader_asset.get_asset_metadata();
		expect_eq(asset_metadata.type, ShaderAsset::asset_type_identifier);
		expect_eq(asset_metadata.version, lt::assets::current_version);

		const auto &metadata = shader_asset.get_metadata();
		expect_eq(metadata.type, ShaderAsset::Type::vertex);

		auto unpakced_blob = shader_asset.unpack(ShaderAsset::BlobTag::code);
		expect_eq(unpakced_blob.size(), blob_size);

		for (auto idx : std::views::iota(0u, blob_size))
		{
			expect_eq(unpakced_blob[idx], static_cast<byte>(idx));
		}
	};
};
