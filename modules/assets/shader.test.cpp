import preliminary;
import assets.metadata;
import assets.shader;
import logger;
import logger;
import test.test;
import test.expects;

using ::lt::assets::AssetMetadata;
using ::lt::assets::BlobMetadata;
using ::lt::assets::ShaderAsset;
using ::lt::test::Case;
using ::lt::test::expect_eq;
using ::lt::test::expect_throw;
using ::lt::test::expect_true;
using ::lt::test::Suite;
using ::lt::test::operator""_suite;

const auto test_data_path = std::filesystem::path { "./data/test_assets" };
const auto tmp_path = std::filesystem::path { "/tmp/lt_assets_tests/" };

Suite raii = "shader_raii"_suite = [] {
	std::filesystem::current_path(test_data_path);
	std::filesystem::create_directories(tmp_path);

	Case { "happy path won't throw" } = [] {
		auto shader_asset = ShaderAsset { "triangle.frag.asset" };
	};

	Case { "many won't freeze/throw" } = [] {
		for (auto idx : std::views::iota(0u, 1'000u))
		{
			ignore = idx;
			auto shader_asset = ShaderAsset { "triangle.frag.asset" };
		}
	};

	Case { "unhappy path throws" } = [] {
		// non-existent file
		expect_throw([] { ShaderAsset { "path" }; });

		// incompatible type
		expect_throw([] { ShaderAsset { "dummytext" }; });

		// random stressing
		expect_throw([] {
			for (auto idx : std::views::iota(0u, 1'000u))
			{
				auto shader_asset = ShaderAsset { std::to_string(idx) };
			}
		});
	};
};

Suite packing = "shader_pack"_suite = [] {
	Case { "" } = [] {
		const auto out_path = tmp_path / "shader_packing";
		auto dummy_blob = lt::assets::Blob {};
		for (auto idx : std::views::iota(0u, 255u))
		{
			dummy_blob.emplace_back(static_cast<byte>(idx));
		}

		const auto expected_size =                    //
		    sizeof(AssetMetadata::type)               //
		    + sizeof(AssetMetadata::version)          //
		    + sizeof(ShaderAsset::Metadata::type)     //
		    + sizeof(BlobMetadata::tag)               //
		    + sizeof(BlobMetadata::offset)            //
		    + sizeof(BlobMetadata::compression_type)  //
		    + sizeof(BlobMetadata::compressed_size)   //
		    + sizeof(BlobMetadata::uncompressed_size) //
		    + dummy_blob.size();

		ShaderAsset::pack(
		    out_path,
		    lt::assets::AssetMetadata {
		        .version = lt::assets::current_version,
		        .type = ShaderAsset::asset_type_identifier,
		    },
		    ShaderAsset::Metadata {
		        .type = ShaderAsset::Type::vertex,
		    },
		    std::move(dummy_blob)
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

		auto blob = shader_asset.unpack(ShaderAsset::BlobTag::code);
		expect_eq(blob.size(), 255u);

		for (auto idx : std::views::iota(0u, 255u))
		{
			expect_eq(blob[idx], static_cast<byte>(idx));
		}
	};
};
