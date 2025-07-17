#pragma once

#include <math/vec4.hpp>
#include <utility>

namespace lt {

class Texture;

struct SpriteRendererComponent
{
	SpriteRendererComponent() = default;

	SpriteRendererComponent(const SpriteRendererComponent &) = default;

	SpriteRendererComponent(
	    Ref<Texture> _texture,
	    const math::vec4 &_tint = math::vec4 { 1.0f, 1.0f, 1.0f, 1.0f }
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

	math::vec4 tint {};
};

} // namespace lt
