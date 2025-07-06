#pragma once

#include <engine/scene/entity.hpp>
#include <mirror/panel/panel.hpp>

namespace Light {

class PropertiesPanel: public Panel
{
public:
	PropertiesPanel() = default;

	void on_user_interface_update();

	void set_entity_context(const Entity &entity);

private:
	void draw_vec3_control(
	    const std::string &label,
	    glm::vec3 &values,
	    float reset_value = 0.0f,
	    float column_width = 100.0f
	);

	template<typename ComponentType, typename UIFunction>
	void draw_component(const std::string &name, Entity entity, UIFunction function);

	Entity m_entity_context;
};


} // namespace Light
