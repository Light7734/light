#pragma once

namespace Light {

class RendererProgram
{
	virtual void map() = 0;

	virtual void un_map() = 0;

	virtual void bind() = 0;

public:
	virtual ~RendererProgram() = default;
};

} // namespace Light
