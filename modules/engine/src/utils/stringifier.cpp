#include <renderer/graphics_context.hpp>
#include <engine/utils/stringifier.hpp>
#include <glad/gl.h>
#include <spdlog/common.h>

namespace Light {

auto Stringifier::glDebugMsgSeverity(unsigned int severity) -> std::string
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_NOTIFICATION: return "GL_DEBUG_SEVERITY_NOTIFICATION";
	case GL_DEBUG_SEVERITY_LOW: return "GL_DEBUG_SEVERITY_LOW";
	case GL_DEBUG_SEVERITY_MEDIUM: return "GL_DEBUG_SEVERITY_MEDIUM";
	case GL_DEBUG_SEVERITY_HIGH: return "GL_DEBUG_SEVERITY_HIGH";
	default: return "UNKNOWN";
	}
}

auto Stringifier::glDebugMsgSource(unsigned int source) -> std::string
{
	switch (source)
	{
	case GL_DEBUG_SOURCE_API: return "GL_DEBUG_SOURCE_API";
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
	case GL_DEBUG_SOURCE_SHADER_COMPILER: return "GL_DEBUG_SOURCE_SHADER_COMPILER";
	case GL_DEBUG_SOURCE_THIRD_PARTY: return "GL_DEBUG_SOURCE_THIRD_PARTY";
	case GL_DEBUG_SOURCE_APPLICATION: return "GL_DEBUG_SOURCE_APPLICATION";
	case GL_DEBUG_SOURCE_OTHER: return "GL_DEBUG_SOURCE_OTHER";
	default: return "UNKNOWN";
	}
}

auto Stringifier::glDebugMsgType(unsigned int type) -> std::string
{
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR: return "GL_DEBUG_TYPE_ERROR";
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
	case GL_DEBUG_TYPE_PORTABILITY: return "GL_DEBUG_TYPE_PORTABILITY";
	case GL_DEBUG_TYPE_PERFORMANCE: return "GL_DEBUG_TYPE_PERFORMANCE";
	case GL_DEBUG_TYPE_MARKER: return "GL_DEBUG_TYPE_MARKER";
	case GL_DEBUG_TYPE_PUSH_GROUP: return "GL_DEBUG_TYPE_PUSH_GROUP";
	case GL_DEBUG_TYPE_POP_GROUP: return "GL_DEBUG_TYPE_POP_GROUP";
	case GL_DEBUG_TYPE_OTHER: return "GL_DEBUG_TYPE_OTHER";
	default: return "UNKNOWN";
	}
}

auto Stringifier::spdlogLevel(unsigned int level) -> std::string
{
	switch (level)
	{
	case SPDLOG_LEVEL_TRACE: return "SPDLOG_LEVEL_TRACE";
	case SPDLOG_LEVEL_DEBUG: return "SPDLOG_LEVEL_DEBUG";
	case SPDLOG_LEVEL_INFO: return "SPDLOG_LEVEL_INFO";
	case SPDLOG_LEVEL_WARN: return "SPDLOG_LEVEL_WARN";
	case SPDLOG_LEVEL_ERROR: return "SPDLOG_LEVEL_ERROR";
	case SPDLOG_LEVEL_CRITICAL: return "SPDLOG_LEVEL_CRITICAL";
	case SPDLOG_LEVEL_OFF: return "SPDLOG_LEVEL_OFF";
	default: return "UNKNOWN";
	}
}

auto Stringifier::graphics_api_to_string(GraphicsAPI api) -> std::string
{
	switch (api)
	{
	case Light::GraphicsAPI::Default: return "Default";
	case Light::GraphicsAPI::OpenGL: return "OpenGL";
	case Light::GraphicsAPI::DirectX: return "DirectX";
	case Light::GraphicsAPI::Vulkan: return "Vulkan";
	case Light::GraphicsAPI::Metal: return "Metal";
	default: return "UNKNOWN";
	}
}

} // namespace Light
