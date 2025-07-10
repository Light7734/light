#pragma once

#include <ecs/entity.hpp>
#include <ecs/scene.hpp>

namespace YAML {

class Emitter;

}

namespace lt {

class SceneSerializer
{
public:
	SceneSerializer(const Ref<Scene> &scene);

	void serialize(const std::string &filePath);

	auto deserialize(const std::string &file_path) -> bool;

	void serialize_binary(const std::string &file_path);

	auto deserialize_binary(const std::string &file_path) -> bool;

private:
	Ref<Scene> m_scene;

	void serialize_entity(YAML::Emitter &out, Entity entity);
};


} // namespace lt
