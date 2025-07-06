#pragma once

#include <engine/base/base.hpp>
#include <engine/scene/entity.hpp>
#include <engine/scene/scene.hpp>
#include <yaml-cpp/yaml.h>

namespace Light {

class SceneSerializer
{
public:
	SceneSerializer(const Ref<Scene> &scene);

	void serialize(const std::string &file_path);

	auto deserialize(const std::string &file_path) -> bool;

	void serialize_binary(const std::string &file_path);

	auto deserialize_binary(const std::string &file_path) -> bool;

private:
	Ref<Scene> m_scene;

	void serialize_entity(YAML::Emitter &out, Entity entity);
};


} // namespace Light
