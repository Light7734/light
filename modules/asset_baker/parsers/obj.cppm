export module bakers.obj;

import preliminary;
import assets.metadata;
import assets.model;
import math.vec2;
import math.vec3;
import logger;

export auto parse_obj(const std::filesystem::path &in_path) -> lt::assets::ModelAsset::PackData
{
	using lt::assets::ModelAsset;

	auto stream = std::ifstream(in_path);
	ensure(stream.is_open(), "Failed to open model at: {}", in_path.string());

	stream.seekg(0, std::ios::end);
	const auto size = stream.tellg();
	stream.seekg(0, std::ios::beg);

	auto vertices = std::vector<ModelAsset::Vertex> {};

	auto positions = std::vector<lt::math::vec3> {};
	auto texcoords = std::vector<lt::math::vec2> {};
	auto normals = std::vector<lt::math::vec3> {};

	auto indices = std::vector<u32> {};

	auto line = std::string {};

	std::string face_word {};
	std::string face_token {};
	while (std::getline(stream, line))
	{
		if (line.starts_with("v "))
		{
			auto &[x, y, z] = positions.emplace_back();
			std::stringstream { line.subview(2) } >> x >> y >> z;
		}

		if (line.starts_with("vt "))
		{
			auto &[u, v] = texcoords.emplace_back();
			std::stringstream { line.subview(3) } >> u >> v;
		}

		if (line.starts_with("vn "))
		{
			auto &[x, y, z] = normals.emplace_back();
			std::stringstream { line.subview(3) } >> x >> y >> z;
		}

		if (line.starts_with("f "))
		{
			auto outer_iss = std::istringstream { line.subview(2) };

			auto count = u32 {};

			while (outer_iss >> face_word)
			{
				auto &[position, texcoord, normal] = vertices.emplace_back();
				auto innter_iss = std::istringstream { face_word };

				std::getline(innter_iss, face_token, '/');
				position = positions[std::stoi(face_token) - 1];

				std::getline(innter_iss, face_token, '/');
				texcoord = texcoords[std::stoi(face_token) - 1];

				std::getline(innter_iss, face_token, '/');
				normal = normals[std::stoi(face_token) - 1];
				++count;
			}

			const auto anchor_idx = vertices.size() - count;
			for (auto idx = 1; (idx + 1) < count; ++idx)
			{
				indices.emplace_back(anchor_idx);
				indices.emplace_back(anchor_idx + idx);
				indices.emplace_back(anchor_idx + idx + 1);
			}
		}
	}

	return ModelAsset::PackData {
		.asset_metadata = { 
            .version = lt::assets::current_version,
            .type = ModelAsset::asset_magic_bytes, 
        },
		.vertices = vertices,
		.indices = indices,
	};
};
