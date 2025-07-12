#include <asset_parser/assets/text.hpp>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <renderer/gl/shader.hpp>

namespace lt {

glShader::glShader(
    const Ref<Assets::TextAsset> &vertex_asset,
    const Ref<Assets::TextAsset> &pixel_asset
)
    : m_shader_id(glCreateProgram())
{
	auto vertex_blob_metadata = vertex_asset->get_blob_metadata(Assets::BlobMetadata::Tag::text);
	auto pixel_blob_metadata = pixel_asset->get_blob_metadata(Assets::BlobMetadata::Tag::text);

	auto vertex_blob = Assets::Blob(vertex_blob_metadata.uncompressed_size);
	auto pixel_blob = Assets::Blob(pixel_blob_metadata.uncompressed_size);

	vertex_asset->unpack_blob(vertex_blob_metadata.tag, vertex_blob.data(), vertex_blob.size());
	pixel_asset->unpack_blob(pixel_blob_metadata.tag, pixel_blob.data(), pixel_blob.size());

	auto vertex_source = std::string {
		reinterpret_cast<char *>(vertex_blob.data()),
		reinterpret_cast<char *>(vertex_blob.data()) + vertex_blob.size(), // NOLINT
	};

	auto pixel_source = std::string {
		reinterpret_cast<char *>(pixel_blob.data()),
		reinterpret_cast<char *>(pixel_blob.data()) + pixel_blob.size(), // NOLINT
	};

	const auto vertex_shader = compile_shader(vertex_source, Shader::Stage::vertex);
	const auto pixel_shader = compile_shader(pixel_source, Shader::Stage::pixel);

	glAttachShader(m_shader_id, vertex_shader);
	glAttachShader(m_shader_id, pixel_shader);

	glLinkProgram(m_shader_id);

	glDeleteShader(vertex_shader);
	glDeleteShader(pixel_shader);
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

auto glShader::compile_shader(const std::string &source, Shader::Stage stage) -> unsigned int
{
	// &(address of) needs an lvalue
	const auto *lvalue_source = source.c_str();
	auto shader = glCreateShader(
	    stage == Shader::Stage::vertex   ? GL_VERTEX_SHADER :
	    stage == Shader::Stage::pixel    ? GL_FRAGMENT_SHADER :
	    stage == Shader::Stage::geometry ? GL_GEOMETRY_SHADER :
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
		    stage == Shader::Stage::vertex ? "Vertex" : "Pixel",
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

} // namespace lt
