#include <engine/debug/exceptions.hpp>
#include <engine/utils/stringifier.hpp>
#include <glad/gl.h>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

namespace Light {

FailedAssertion::FailedAssertion(const char *file, int line)
{
	LOG(critical, "Assertion failed in: {} (line {})", file, line);
}

glException::glException(unsigned int source, unsigned int type, unsigned int id, const char *msg)
{
	// #todo: improve
	LOG(critical, "________________________________________");
	LOG(critical, "glException::glException::");
	// LOG(critical, "        Severity: {}",
	// Stringifier::glDebugMsgSeverity(GL_DEBUG_SEVERITY_HIGH));
	LOG(critical, "        Source  : {}", Stringifier::glDebugMsgSource(source));
	LOG(critical, "        Type    : {}", Stringifier::glDebugMsgType(type));
	LOG(critical, "        ID      : {}", id);
	// LOG(critical, "        Vendor  : {}", glGetString(GL_VENDOR));
	// LOG(critical, "        Renderer: {}", glGetString(GL_RENDERER));
	// LOG(critical, "        Version : {}", glGetString(GL_VERSION));
	// LOG(critical, "        critical, SVersion: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
	LOG(critical, "        {}", msg);
	LOG(critical, "________________________________________");
}

#ifdef LIGHT_PLATFORM_WINDOWS
dxException::dxException(long hr, const char *file, int line)
{
	char *message;
	FormatMessageA(
	    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	    nullptr,
	    hr,
	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	    (LPSTR)(&message),
	    NULL,
	    nullptr
	);

	// #todo: improve
	LOG(critical, "________________________________________");
	LOG(critical, "dxException::dxException::");
	LOG(critical, "        File: {}, Line: {}", file, line);
	LOG(critical, "        {}", message);
	LOG(critical, "________________________________________");

	LocalFree(message);
}
#endif

} // namespace Light
