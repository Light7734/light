#pragma once

#include "Base/Base.hpp"
#include "Graphics/Shader.hpp"
#include "Utility/FileManager.hpp"

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
