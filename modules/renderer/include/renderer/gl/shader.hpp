#pragma once

#include <renderer/shader.hpp>

namespace lt {

class glShader: public Shader
{
public:
	glShader(const Ref<Assets::TextAsset> &vertex_asset, const Ref<Assets::TextAsset> &pixel_asset);

	~glShader() override;

	void bind() override;

	void un_bind() override;

private:
	unsigned int compile_shader(const std::string &source, Shader::Stage stage);

	unsigned int m_shader_id { 0u };
};

} // namespace lt
