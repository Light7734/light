#include <engine/platform/graphics/opengl/shader.hpp>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>

namespace Light {

glShader::glShader(BasicFileHandle vertexFile, BasicFileHandle pixelFile) 
{
	// create
	m_shader_id = glCreateProgram();

	std::string const vertexSource(vertexFile.get_data(), vertexFile.get_data() + vertexFile.get_size());
	std::string const pixelSource(pixelFile.get_data(), pixelFile.get_data() + pixelFile.get_size());

	unsigned int const vertexShader = compile_shader(vertexSource, Shader::Stage::VERTEX);
	unsigned int const pixelShader = compile_shader(pixelSource, Shader::Stage::PIXEL);

	// attach shaders
	glAttachShader(m_shader_id, vertexShader);
	glAttachShader(m_shader_id, pixelShader);

	// link shader program
	glLinkProgram(m_shader_id);

	// delete shaders (free memory)
	glDeleteShader(vertexShader);
	glDeleteShader(pixelShader);
}

glShader::~glShader()
{
	glDeleteProgram(m_shader_id);
}

void glShader::bind()
{
	glUseProgram(m_shader_id);
}

void glShader::un_bind()
{
	glUseProgram(NULL);
}

// shaderc::SpvCompilationResult glShader::compile_glsl(basic_file_handle file, Shader::Stage stage)
// {
// 	// compile options
// 	shaderc::CompileOptions options;
// 	options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
// 	options.SetOptimizationLevel(shaderc_optimization_level_performance);
//
// 	// compile
// 	shaderc::Compiler compiler;
// 	shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(reinterpret_cast<const
// char*>(file.GetData()), stage == Shader::Stage::VERTEX ?
// shaderc_shader_kind::shaderc_vertex_shader : shaderc_shader_kind::shaderc_fragment_shader,
// file.GetName().c_str(), options);
//
// 	// log error
// 	if (result.GetCompilationStatus() != shaderc_compilation_status_success)
// 	{
// 		log_err("Failed to compile {} shader at {}...", stage == Shader::Stage::VERTEX ?
// "vertex" : "pixel", file.GetPath()); 		log_err("    {}", result.GetErrorMessage());
// 	}
//
// 	return result;
// }

auto glShader::compile_shader(const std::string& source, Shader::Stage stage) -> unsigned int
{
	// &(address of) needs an lvalue
	const auto *lvalue_source = source.c_str();
	auto shader = glCreateShader(
	    stage == Shader::Stage::VERTEX   ? GL_VERTEX_SHADER :
	    stage == Shader::Stage::PIXEL    ? GL_FRAGMENT_SHADER :
	    stage == Shader::Stage::GEOMETRY ? GL_GEOMETRY_SHADER :
	                                       NULL
	);

	// compile
	glShaderSource(shader, 1, &lvalue_source, nullptr);
	glCompileShader(shader);

	// check
	auto isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		auto logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

		auto *errorLog = (char *)alloca(logLength);
		glGetShaderInfoLog(shader, logLength, &logLength, &errorLog[0]);

		log_err(
		    "glShader::glShader: failed to compile {} shader:\n        {}",
		    stage == Shader::Stage::VERTEX ? "Vertex" : "Pixel",
		    errorLog
		);

		return NULL;
	}
#define LIGHT_OPENGL_ENABLE_SHADER_INFO_LOG
#ifdef LIGHT_OPENGL_ENABLE_SHADER_INFO_LOG
	// info log
	{
		auto logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength)
		{
			char *infoLog = (char *)alloca(logLength);
			glGetShaderInfoLog(shader, logLength, &logLength, &infoLog[0]);

			log_wrn("Shader info: {}", infoLog);
		}
	}
#endif

	return shader;
}

} // namespace Light
