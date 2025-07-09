#pragma once

#include <asset_parser/assets/text.hpp>
#include <engine/base/base.hpp>
#include <glm/glm.hpp>

namespace Light {

class SharedContext;

class Shader
{
public:
	enum Stage
	{
		none = 0,

		vertex,
		pixel,
		geometry,
	};

	static auto create(
	    Assets::Blob vertex_blob,
	    Assets::Blob pixel_blob,
	    const Ref<SharedContext> &shared_context
	) -> Ref<Shader>;

	virtual ~Shader() = default;

	virtual void bind() = 0;

	virtual void un_bind() = 0;

protected:
	Shader() = default;
};

} // namespace Light
