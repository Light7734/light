#include <engine/events/window.hpp>
#include <engine/graphics/blender.hpp>        // required for forward declaratio>
#include <engine/graphics/buffers.hpp>        // required for forward declaratio>
#include <engine/graphics/render_command.hpp> // required for forward declaratio>
#include <engine/graphics/renderer.hpp>       // required for forward declaratio>
#include <engine/platform/graphics/opengl/graphics_context.hpp>
#include <engine/user_interface/user_interface.hpp> // required for forward declaratio>
#include <engine/utils/resource_manager.hpp>        // required for forward declaratio>
#include <glad/gl.h>

#ifndef STOP_FUCKING_ORDERING_THESE_THE_WRONG_WAY_CLANG_FORMAT____
	#include <GLFW/glfw3.h>
#endif

namespace Light {

glGraphicsContext::glGraphicsContext(GLFWwindow *windowHandle): m_window_handle(windowHandle)
{
	m_graphics_api = GraphicsAPI::OpenGL;
	glfwMakeContextCurrent(windowHandle);
	lt_assert(gladLoadGL(glfwGetProcAddress), "Failed to initialize opengl (glad)");

	set_debug_message_callback();
}

void glGraphicsContext::log_debug_data()
{
	log_inf("________________________________________");
	log_inf("GraphicsContext::");
	log_inf("        API     : OpenGL");
	log_inf("________________________________________");
}

void glGraphicsContext::set_debug_message_callback()
{
	// determine log level
	// #todo: set filters from config.h
#if defined(LIGHT_DEBUG)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

	GLuint ids[] = { 131185 };
	glDebugMessageControl(
	    GL_DEBUG_SOURCE_API,
	    GL_DEBUG_TYPE_OTHER,
	    GL_DONT_CARE,
	    _countof(ids),
	    ids,
	    GL_FALSE
	);
#elif defined(LIGHT_RELEASE)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_FALSE);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
	glDebugMessageControl(
	    GL_DONT_CARE,
	    GL_DONT_CARE,
	    GL_DEBUG_SEVERITY_MEDIUM,
	    0,
	    nullptr,
	    GL_TRUE
	);
#else // LIGHT_DIST
	return;
#endif

	/* setup message callback */
	glDebugMessageCallback(
	    [](unsigned int source,
	       unsigned int type,
	       unsigned int id,
	       unsigned int severity,
	       int length,
	       const char *message,
	       const void *userParam) {
		    switch (severity)
		    {
		    case GL_DEBUG_SEVERITY_HIGH:
			    // throw glException(source, type, id, message);
			    return;

		    case GL_DEBUG_SEVERITY_MEDIUM:
		    case GL_DEBUG_SEVERITY_LOW:
			    log_wrn(
			        "glMessageCallback: Severity: {} :: Source: {} :: Type: {} :: ID: {}",
			        Stringifier::glDebugMsgSeverity(severity),
			        Stringifier::glDebugMsgSource(source),
			        Stringifier::glDebugMsgType(type),
			        id
			    );
			    log_wrn("      {}", message);
			    return;

		    case GL_DEBUG_SEVERITY_NOTIFICATION:
			    log_wrn(
			        "Severity: {} :: Source: {} :: Type: {} :: ID: {}",
			        Stringifier::glDebugMsgSeverity(severity),
			        Stringifier::glDebugMsgSource(source),
			        Stringifier::glDebugMsgType(type),
			        id
			    );
			    log_trc("        {}", message);
			    return;
		    }
	    },
	    nullptr
	);
}

} // namespace Light
