#pragma once

#include <engine/base/base.hpp>
#include <glm/glm.hpp>

namespace Light {

class Texture;

struct SpriteRendererComponent
{
	SpriteRendererComponent() = default;

	SpriteRendererComponent(const SpriteRendererComponent &) = default;

	SpriteRendererComponent(
	    Ref<Texture> _texture,
	    const glm::vec4 &_tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
	)
	    : texture(_texture)
	    , tint(_tint)
	{
	}

	operator Ref<Texture>()
	{
		return texture;
	}

	Ref<Texture> texture;

	glm::vec4 tint;
};

} // namespace Light
