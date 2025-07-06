#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/shader.hpp>
#include <engine/utils/file_manager.hpp>

namespace Light {

class glShader: public Shader
{
public:
	glShader(BasicFileHandle vertexFile, BasicFileHandle pixelFile);

	~glShader() override;

	void bind() override;

	void un_bind() override;

private:
	unsigned int compile_shader(const std::string& source, Shader::Stage stage);

	unsigned int m_shader_id{0u};
};

} // namespace Light
