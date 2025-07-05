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

	void serialize(const std::string &filePath);
	bool deserialize(const std::string &filePath);

	void serialize_binary(const std::string &filePath);
	bool deserialize_binary(const std::string &filePath);

private:
	void serialize_entity(YAML::Emitter &out, Entity entity);

private:
	Ref<Scene> m_scene;
};


} // namespace Light
