#pragma once

#include <engine/base/base.hpp>

namespace Light {

class OrthographicCamera;

class RendererProgram
{
	virtual void map() = 0;

	virtual void un_map() = 0;

	virtual void bind() = 0;
};

} // namespace Light
