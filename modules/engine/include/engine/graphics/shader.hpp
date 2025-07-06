#pragma once

#include <engine/base/base.hpp>
#include <engine/utils/file_manager.hpp>
#include <glm/glm.hpp>

namespace Light {

class SharedContext;

class Shader
{
public:
	enum Stage
	{
		NONE = 0,
		VERTEX = 1,
		PIXEL = 2,
		GEOMETRY = 3
	};

	static auto create(
	    const BasicFileHandle& vertexFile,
	    const BasicFileHandle& pixelFile,
	    const Ref<SharedContext>& sharedContext
	) -> Ref<Shader>;

	virtual ~Shader() = default;

	virtual void bind() = 0;

	virtual void un_bind() = 0;

protected:
	Shader() = default;
};

} // namespace Light
