#include <engine/platform/graphics/opengl/shader.hpp>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>

namespace Light {

glShader::glShader(BasicFileHandle vertexFile, BasicFileHandle pixelFile): m_shader_id(0u)
{
	// create
	m_shader_id = glCreateProgram();

	std::string vertexSource(vertexFile.get_data(), vertexFile.get_data() + vertexFile.get_size());
	std::string pixelSource(pixelFile.get_data(), pixelFile.get_data() + pixelFile.get_size());

	unsigned int vertexShader = compile_shader(vertexSource, Shader::Stage::VERTEX);
	unsigned int pixelShader = compile_shader(pixelSource, Shader::Stage::PIXEL);

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
// 		lt_log(err, "Failed to compile {} shader at {}...", stage == Shader::Stage::VERTEX ? "vertex" :
// "pixel", file.GetPath()); 		lt_log(err, "    {}", result.GetErrorMessage());
// 	}
//
// 	return result;
// }

unsigned int glShader::compile_shader(std::string source, Shader::Stage stage)
{
	// &(address of) needs an lvalue
	const char *lvalue_source = source.c_str();
	unsigned int shader = glCreateShader(
	    stage == Shader::Stage::VERTEX   ? GL_VERTEX_SHADER :
	    stage == Shader::Stage::PIXEL    ? GL_FRAGMENT_SHADER :
	    stage == Shader::Stage::GEOMETRY ? GL_GEOMETRY_SHADER :
	                                       NULL
	);

	// compile
	glShaderSource(shader, 1, &lvalue_source, NULL);
	glCompileShader(shader);

	// check
	int isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		int logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

		char *errorLog = (char *)alloca(logLength);
		glGetShaderInfoLog(shader, logLength, &logLength, &errorLog[0]);

		lt_log(err,
		    "glShader::glShader: failed to compile {} shader:\n        {}",
		    stage == Shader::Stage::VERTEX ? "Vertex" : "Pixel",
		    errorLog);

		return NULL;
	}
#define LIGHT_OPENGL_ENABLE_SHADER_INFO_LOG
#ifdef LIGHT_OPENGL_ENABLE_SHADER_INFO_LOG
	// info log
	{
		int logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength)
		{
			char *infoLog = (char *)alloca(logLength);
			glGetShaderInfoLog(shader, logLength, &logLength, &infoLog[0]);

			lt_log(warn, infoLog);
		}
	}
#endif

	return shader;
}

} // namespace Light
