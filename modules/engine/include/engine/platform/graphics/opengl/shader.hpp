#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/shader.hpp>
#include <engine/utils/file_manager.hpp>

namespace Light {

class glShader: public Shader
{
private:
	unsigned int m_ShaderID;

public:
	glShader(BasicFileHandle vertexFile, BasicFileHandle pixelFile);
	~glShader();

	void Bind() override;
	void UnBind() override;

private:
	// shaderc::SpvCompilationResult CompileGLSL(BasicFileHandle file, Shader::Stage stage);

	unsigned int CompileShader(std::string source, Shader::Stage stage);
};

} // namespace Light
