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

public:
	static Ref<Shader> create(
	    basic_file_handle vertexFile,
	    basic_file_handle pixelFile,
	    Ref<SharedContext> sharedContext
	);

	virtual ~Shader() = default;

	virtual void bind() = 0;
	virtual void un_bind() = 0;

protected:
	Shader() = default;
};

} // namespace Light
