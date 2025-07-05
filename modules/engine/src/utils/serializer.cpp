#include <engine/graphics/texture.hpp>
#include <engine/scene/components.hpp>
#include <engine/utils/resource_manager.hpp>
#include <engine/utils/serializer.hpp>

namespace YAML {

template<>
struct convert<glm::vec3>
{
	static Node encode(const glm::vec3 &rhs)
	{
		Node node;
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		node.push_back(rhs.z);
		return node;
	}

	static bool decode(const Node &node, glm::vec3 &rhs)
	{
		if (!node.IsSequence() || node.size() != 3)
			return false;

		rhs.x = node[0].as<float>();
		rhs.y = node[1].as<float>();
		rhs.z = node[2].as<float>();
		return true;
	}
};

template<>
struct convert<glm::vec4>
{
	static Node encode(const glm::vec4 &rhs)
	{
		Node node;
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		node.push_back(rhs.z);
		node.push_back(rhs.w);
		return node;
	}

	static bool decode(const Node &node, glm::vec4 &rhs)
	{
		if (!node.IsSequence() || node.size() != 4)
			return false;

		rhs.x = node[0].as<float>();
		rhs.y = node[1].as<float>();
		rhs.z = node[2].as<float>();
		rhs.w = node[3].as<float>();
		return true;
	}
};
} // namespace YAML

namespace Light {

static YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec3 &v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}

static YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec4 &v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
	return out;
}

SceneSerializer::SceneSerializer(const Ref<Scene> &scene): m_scene(scene)
{
}

void SceneSerializer::Serialize(const std::string &filePath)
{
	YAML::Emitter out;
	out << YAML::BeginMap; // Scene
	out << YAML::Key << "Scene" << YAML::Value << "Untitled";

	out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
	for (auto [entityID, storage] : m_scene->m_registry.storage())
	{
		Entity entity = { static_cast<entt::entity>(entityID), m_scene.get() };
		if (!entity.IsValid())
			return;

		SerializeEntity(out, entity);
	};
	out << YAML::EndSeq;
	out << YAML::EndMap;

	std::filesystem::create_directories(filePath.substr(0ull, filePath.find_last_of('\\')));

	std::ofstream fout(filePath);
	if (!fout.is_open())
		LOG(trace, "Failed to create fout at: {}", filePath);
	fout << out.c_str();
}

bool SceneSerializer::Deserialize(const std::string &filePath)
{
	std::ifstream stream(filePath);
	std::stringstream ss;
	ss << stream.rdbuf();

	YAML::Node data = YAML::Load(ss.str());
	if (!data["Scene"])
		return false;

	std::string sceneName = data["Scene"].as<std::string>();
	LOG(trace, "Deserializing scene: '{}'", sceneName);

	auto entities = data["Entities"];
	if (entities)
	{
		/* #TEMPORARY SOLUTION# */
		std::unordered_set<std::string> texturePaths;
		/* #TEMPORARY SOLUTION# */


		for (auto entity : entities)
		{
			uint64_t uuid = entity["Entity"].as<uint64_t>(); // #todo

			std::string name;
			auto tagComponent = entity["TagComponent"];
			if (tagComponent)
				name = tagComponent["Tag"].as<std::string>();

			LOG(trace, "Deserialized entity '{}' : '{}'", uuid, name);

			Entity deserializedEntity = m_scene->CreateEntityWithUUID(name, uuid);

			TagComponent gg = deserializedEntity.GetComponent<TagComponent>();
			LOG(trace, gg.tag);
			auto transformComponent = entity["TransformComponent"];
			if (transformComponent)
			{
				auto &entityTransforomComponent = deserializedEntity
				                                      .GetComponent<TransformComponent>();

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
				                                          .AddComponent<SpriteRendererComponent>();
				entitySpriteRendererComponent.tint = spriteRendererComponent["Tint"].as<glm::vec4>(
				);

				std::string texturePath = spriteRendererComponent["Texture"].as<std::string>();

				if (!texturePaths.contains(texturePath))
				{
					ResourceManager::LoadTexture(texturePath, texturePath);
					texturePaths.insert(texturePath);
				}

				entitySpriteRendererComponent.texture = ResourceManager::GetTexture(texturePath);
			}
			/* #TEMPORARY SOLUTION# */

			auto cameraComponent = entity["CameraComponent"];
			if (cameraComponent)
			{
				auto &entityCameraComponent = deserializedEntity.AddComponent<CameraComponent>();

				const auto &cameraSpecifications = cameraComponent["Camera"];
				entityCameraComponent.camera.SetProjectionType(
				    (SceneCamera::ProjectionType)cameraSpecifications["ProjectionType"].as<int>()
				);

				entityCameraComponent.camera.SetOrthographicSize(
				    cameraSpecifications["OrthographicSize"].as<float>()
				);
				entityCameraComponent.camera.SetOrthographicNearPlane(
				    cameraSpecifications["OrthographicNearPlane"].as<float>()
				);
				entityCameraComponent.camera.SetOrthographicFarPlane(
				    cameraSpecifications["OrthographicFarPlane"].as<float>()
				);

				entityCameraComponent.camera.SetPerspectiveVerticalFOV(
				    cameraSpecifications["PerspectiveVerticalFOV"].as<float>()
				);
				entityCameraComponent.camera.SetPerspectiveNearPlane(
				    cameraSpecifications["PerspectiveNearPlane"].as<float>()
				);
				entityCameraComponent.camera.SetPerspectiveFarPlane(
				    cameraSpecifications["PerspectiveFarPlane"].as<float>()
				);

				entityCameraComponent.camera.SetBackgroundColor(
				    cameraSpecifications["BackgroundColor"].as<glm::vec4>()
				);

				entityCameraComponent.isPrimary = cameraComponent["IsPrimary"].as<bool>();
			}
		}

		return true;
	}

	return false;
}

void SceneSerializer::SerializeBinary(const std::string &filePath)
{
	LOG(err, "NO_IMPLEMENT");
}

bool SceneSerializer::DeserializeBinary(const std::string &filePath)
{
	LOG(err, "NO_IMPLEMENT");
	return false;
}

void SceneSerializer::SerializeEntity(YAML::Emitter &out, Entity entity)
{
	out << YAML::BeginMap;                                           // entity
	out << YAML::Key << "Entity" << YAML::Value << entity.GetUUID(); // dummy uuid

	if (entity.HasComponent<TagComponent>())
	{
		out << YAML::Key << "TagComponent";
		out << YAML::BeginMap; // tag component

		auto &tagComponent = entity.GetComponent<TagComponent>().tag;
		out << YAML::Key << "Tag" << YAML::Value << tagComponent;

		out << YAML::EndMap; // tag component
	}

	if (entity.HasComponent<TransformComponent>())
	{
		out << YAML::Key << "TransformComponent";
		out << YAML::BeginMap; // transform component

		auto &transformComponent = entity.GetComponent<TransformComponent>();

		out << YAML::Key << "Translation" << YAML::Value << transformComponent.translation;
		out << YAML::Key << "Rotation" << YAML::Value << transformComponent.rotation;
		out << YAML::Key << "Scale" << YAML::Value << transformComponent.scale;

		out << YAML::EndMap; // transform component;
	}

	if (entity.HasComponent<SpriteRendererComponent>())
	{
		out << YAML::Key << "SpriteRendererComponent";
		out << YAML::BeginMap; // sprite renderer component;

		auto &spriteRendererComponent = entity.GetComponent<SpriteRendererComponent>();

		out << YAML::Key << "Texture" << YAML::Value
		    << spriteRendererComponent.texture->GetFilePath();
		out << YAML::Key << "Tint" << YAML::Value << spriteRendererComponent.tint;

		out << YAML::EndMap; // sprite renderer component
	}

	// #todo:
	// if(entity.HasComponent<NativeScriptComponent>())

	if (entity.HasComponent<CameraComponent>())
	{
		out << YAML::Key << "CameraComponent";
		out << YAML::BeginMap; // camera component

		auto &cameraComponent = entity.GetComponent<CameraComponent>();

		out << YAML::Key << "Camera" << YAML::Value;
		out << YAML::BeginMap; // camera
		out << YAML::Key << "OrthographicSize" << YAML::Value
		    << cameraComponent.camera.GetOrthographicSize();
		out << YAML::Key << "OrthographicFarPlane" << YAML::Value
		    << cameraComponent.camera.GetOrthographicFarPlane();
		out << YAML::Key << "OrthographicNearPlane" << YAML::Value
		    << cameraComponent.camera.GetOrthographicNearPlane();
		out << YAML::Key << "PerspectiveVerticalFOV" << YAML::Value
		    << cameraComponent.camera.GetPerspectiveVerticalFOV();
		out << YAML::Key << "PerspectiveFarPlane" << YAML::Value
		    << cameraComponent.camera.GetPerspectiveFarPlane();
		out << YAML::Key << "PerspectiveNearPlane" << YAML::Value
		    << cameraComponent.camera.GetPerspectiveNearPlane();
		out << YAML::Key << "ProjectionType" << YAML::Value
		    << (int)cameraComponent.camera.GetProjectionType();
		out << YAML::Key << "BackgroundColor" << YAML::Value
		    << cameraComponent.camera.GetBackgroundColor();
		out << YAML::EndMap; // camera

		out << YAML::Key << "IsPrimary" << YAML::Value << cameraComponent.isPrimary;

		out << YAML::EndMap; // camera component
	}
	out << YAML::EndMap; // entity
}

} // namespace Light
