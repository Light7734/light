#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/shader.hpp>

namespace Light {

class glShader: public Shader
{
public:
	glShader(Assets::Blob vertex_blob, Assets::Blob pixel_blob);

	~glShader() override;

	void bind() override;

	void un_bind() override;

private:
	unsigned int compile_shader(const std::string &source, Shader::Stage stage);

	unsigned int m_shader_id { 0u };
};

} // namespace Light
