#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/shader.hpp>
#include <engine/utils/file_manager.hpp>

namespace Light {

class glShader: public Shader
{
private:
	unsigned int m_shader_id;

public:
	glShader(basic_file_handle vertexFile, basic_file_handle pixelFile);
	~glShader();

	void bind() override;
	void un_bind() override;

private:
	// shaderc::SpvCompilationResult compile_glsl(basic_file_handle file, Shader::Stage stage);

	unsigned int compile_shader(std::string source, Shader::Stage stage);
};

} // namespace Light
