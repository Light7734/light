#pragma once

#include <glm/glm.hpp>
#include <utility>

namespace lt {

class Texture;

struct SpriteRendererComponent
{
	SpriteRendererComponent() = default;

	SpriteRendererComponent(const SpriteRendererComponent &) = default;

	SpriteRendererComponent(
	    Ref<Texture> _texture,
	    const glm::vec4 &_tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
	)
	    : texture(std::move(std::move(_texture)))
	    , tint(_tint)
	{
	}

	operator Ref<Texture>() const
	{
		return texture;
	}

	Ref<Texture> texture;

	glm::vec4 tint {};
};

} // namespace lt
