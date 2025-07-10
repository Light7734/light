#pragma once

#include <glm/glm.hpp>

namespace Assets {

class TextAsset;

} // namespace Assets

namespace Light {

class SharedContext;

class Shader
{
public:
	enum Stage : uint8_t
	{
		none = 0,

		vertex,
		pixel,
		geometry,
	};

	static auto create(
	    Ref<Assets::TextAsset> vertex_asset,
	    Ref<Assets::TextAsset> pixel_asset,
	    const Ref<SharedContext> &shared_context
	) -> Ref<Shader>;

	virtual ~Shader() = default;

	virtual void bind() = 0;

	virtual void un_bind() = 0;

protected:
	Shader() = default;
};

} // namespace Light
