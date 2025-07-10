#include <asset_manager/asset_manager.hpp>
#include <camera/component.hpp>
#include <ecs/components.hpp>
#include <ecs/serializer.hpp>
#include <yaml-cpp/yaml.h>

namespace YAML {

template<>
struct convert<glm::vec3>
{
	static auto encode(const glm::vec3 &rhs) -> Node
	{
		auto node = Node {};
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		node.push_back(rhs.z);
		return node;
	}

	static auto decode(const Node &node, glm::vec3 &rhs) -> bool
	{
		if (!node.IsSequence() || node.size() != 3)
		{
			return false;
		}

		rhs.x = node[0].as<float>();
		rhs.y = node[1].as<float>();
		rhs.z = node[2].as<float>();
		return true;
	}
};

template<>
struct convert<glm::vec4>
{
	static auto encode(const glm::vec4 &rhs) -> Node
	{
		auto node = Node {};
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		node.push_back(rhs.z);
		node.push_back(rhs.w);
		return node;
	}

	static auto decode(const Node &node, glm::vec4 &rhs) -> bool
	{
		if (!node.IsSequence() || node.size() != 4)
		{
			return false;
		}

		rhs.x = node[0].as<float>();
		rhs.y = node[1].as<float>();
		rhs.z = node[2].as<float>();
		rhs.w = node[3].as<float>();
		return true;
	}
};
} // namespace YAML

namespace lt {

auto operator<<(YAML::Emitter &out, const glm::vec3 &v) -> YAML::Emitter &
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}

auto operator<<(YAML::Emitter &out, const glm::vec4 &v) -> YAML::Emitter &
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
	return out;
}

SceneSerializer::SceneSerializer(const Ref<Scene> &scene): m_scene(scene)
{
}

void SceneSerializer::serialize(const std::string &filePath)
{
	auto out = YAML::Emitter {};
	out << YAML::BeginMap; // Scene
	out << YAML::Key << "Scene" << YAML::Value << "Untitled";

	out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
	for (auto [entityID, storage] : m_scene->m_registry.storage())
	{
		auto entity = Entity { static_cast<entt::entity>(entityID), m_scene.get() };
		if (!entity.is_valid())
		{
			return;
		}

		serialize_entity(out, entity);
	};
	out << YAML::EndSeq;
	out << YAML::EndMap;

	std::filesystem::create_directories(filePath.substr(0ull, filePath.find_last_of('\\')));

	auto fout = std::ofstream { filePath };
	if (!fout.is_open())
	{
		log_trc("Failed to create fout at: {}", filePath);
	}

	fout << out.c_str();
}

auto SceneSerializer::deserialize(const std::string &file_path) -> bool
{
	auto stream = std::ifstream { file_path };
	auto ss = std::stringstream {};
	ss << stream.rdbuf();

	auto data = YAML::Load(ss.str());
	if (!data["Scene"])
	{
		return false;
	}

	auto sceneName = data["Scene"].as<std::string>();
	log_trc("Deserializing scene: '{}'", sceneName);

	auto entities = data["Entities"];
	if (entities)
	{
		auto texturePaths = std::unordered_set<std::string> {};

		for (auto entity : entities)
		{
			auto uuid = entity["entity"].as<uint64_t>(); // #todo

			auto name = std::string {};
			auto tagComponent = entity["TagComponent"];
			if (tagComponent)
			{
				name = tagComponent["Tag"].as<std::string>();
			}

			log_trc("Deserialized entity '{}' : '{}'", uuid, name);

			auto deserializedEntity = m_scene->create_entity_with_uuid(name, uuid);

			auto gg = deserializedEntity.get_component<TagComponent>();
			log_trc("tag: {}", gg.tag);
			auto transformComponent = entity["TransformComponent"];
			if (transformComponent)
			{
				auto &entityTransforomComponent = deserializedEntity
				                                      .get_component<TransformComponent>();

				entityTransforomComponent.translation = transformComponent["Translation"]
				                                            .as<glm::vec3>();
				entityTransforomComponent.rotation = transformComponent["Rotation"].as<glm::vec3>();
				entityTransforomComponent.scale = transformComponent["Scale"].as<glm::vec3>();
			}

			/* #TEMPORARY SOLUTION# */
			auto spriteRendererComponent = entity["SpriteRendererComponent"];
			if (spriteRendererComponent)
			{
				auto &entitySpriteRendererComponent = deserializedEntity
				                                          .add_component<SpriteRendererComponent>();
				entitySpriteRendererComponent.tint = spriteRendererComponent["Tint"].as<glm::vec4>(
				);

				auto texturePath = spriteRendererComponent["Texture"].as<std::string>();

				if (!texturePaths.contains(texturePath))
				{
					AssetManager::load_texture(texturePath, texturePath);
					texturePaths.insert(texturePath);
				}

				entitySpriteRendererComponent.texture = AssetManager::get_texture(texturePath);
			}
			/* #TEMPORARY SOLUTION# */

			auto cameraComponent = entity["CameraComponent"];
			if (cameraComponent)
			{
				auto &entityCameraComponent = deserializedEntity.add_component<CameraComponent>();

				const auto &cameraSpecifications = cameraComponent["Camera"];
				entityCameraComponent.camera.set_projection_type(
				    (SceneCamera::ProjectionType)cameraSpecifications["ProjectionType"].as<int>()
				);

				entityCameraComponent.camera.set_orthographic_size(
				    cameraSpecifications["OrthographicSize"].as<float>()
				);
				entityCameraComponent.camera.set_orthographic_near_plane(
				    cameraSpecifications["OrthographicNearPlane"].as<float>()
				);
				entityCameraComponent.camera.set_orthographic_far_plane(
				    cameraSpecifications["OrthographicFarPlane"].as<float>()
				);

				entityCameraComponent.camera.set_perspective_vertical_fov(
				    cameraSpecifications["PerspectiveVerticalFOV"].as<float>()
				);
				entityCameraComponent.camera.set_perspective_near_plane(
				    cameraSpecifications["PerspectiveNearPlane"].as<float>()
				);
				entityCameraComponent.camera.set_perspective_far_plane(
				    cameraSpecifications["PerspectiveFarPlane"].as<float>()
				);

				entityCameraComponent.camera.set_background_color(
				    cameraSpecifications["BackgroundColor"].as<glm::vec4>()
				);

				entityCameraComponent.isPrimary = cameraComponent["IsPrimary"].as<bool>();
			}
		}

		return true;
	}

	return false;
}

void SceneSerializer::serialize_binary(const std::string & /*filePath*/)
{
	log_err("NO_IMPLEMENT");
}

auto SceneSerializer::deserialize_binary(const std::string & /*filePath*/) -> bool
{
	log_err("NO_IMPLEMENT");
	return false;
}

void SceneSerializer::serialize_entity(YAML::Emitter &out, Entity entity)
{
	out << YAML::BeginMap;                                            // entity
	out << YAML::Key << "entity" << YAML::Value << entity.get_uuid(); // dummy uuid

	if (entity.has_component<TagComponent>())
	{
		out << YAML::Key << "TagComponent";
		out << YAML::BeginMap; // tag component

		auto &tagComponent = entity.get_component<TagComponent>().tag;
		out << YAML::Key << "Tag" << YAML::Value << tagComponent;

		out << YAML::EndMap; // tag component
	}

	if (entity.has_component<TransformComponent>())
	{
		out << YAML::Key << "TransformComponent";
		out << YAML::BeginMap; // transform component

		auto &transformComponent = entity.get_component<TransformComponent>();

		out << YAML::Key << "Translation" << YAML::Value << transformComponent.translation;
		out << YAML::Key << "Rotation" << YAML::Value << transformComponent.rotation;
		out << YAML::Key << "Scale" << YAML::Value << transformComponent.scale;

		out << YAML::EndMap; // transform component;
	}

	if (entity.has_component<SpriteRendererComponent>())
	{
		// TODO(Light): get scene serialization/de-serialization working.
		// out << YAML::Key << "SpriteRendererComponent";
		// out << YAML::BeginMap; // sprite renderer component;

		// auto &spriteRendererComponent = entity.get_component<SpriteRendererComponent>();

		// out << YAML::Key << "Texture" << YAML::Value
		//     << spriteRendererComponent.texture->GetFilePath();
		// out << YAML::Key << "Tint" << YAML::Value << spriteRendererComponent.tint;

		// out << YAML::EndMap; // sprite renderer component
	}

	// #todo:
	// if(entity.has_component<NativeScriptComponent>())

	if (entity.has_component<CameraComponent>())
	{
		out << YAML::Key << "CameraComponent";
		out << YAML::BeginMap; // camera component

		auto &cameraComponent = entity.get_component<CameraComponent>();

		out << YAML::Key << "Camera" << YAML::Value;
		out << YAML::BeginMap; // camera
		out << YAML::Key << "OrthographicSize" << YAML::Value
		    << cameraComponent.camera.get_orthographic_size();
		out << YAML::Key << "OrthographicFarPlane" << YAML::Value
		    << cameraComponent.camera.get_orthographic_far_plane();
		out << YAML::Key << "OrthographicNearPlane" << YAML::Value
		    << cameraComponent.camera.get_orthographic_near_plane();
		out << YAML::Key << "PerspectiveVerticalFOV" << YAML::Value
		    << cameraComponent.camera.get_perspective_vertical_fov();
		out << YAML::Key << "PerspectiveFarPlane" << YAML::Value
		    << cameraComponent.camera.get_perspective_far_plane();
		out << YAML::Key << "PerspectiveNearPlane" << YAML::Value
		    << cameraComponent.camera.get_perspective_near_plane();
		out << YAML::Key << "ProjectionType" << YAML::Value
		    << (int)cameraComponent.camera.get_projection_type();
		out << YAML::Key << "BackgroundColor" << YAML::Value
		    << cameraComponent.camera.get_background_color();
		out << YAML::EndMap; // camera

		out << YAML::Key << "IsPrimary" << YAML::Value << cameraComponent.isPrimary;

		out << YAML::EndMap; // camera component
	}
	out << YAML::EndMap; // entity
}

} // namespace lt
