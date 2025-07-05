#include <engine/debug/exceptions.hpp>
#include <engine/utils/stringifier.hpp>
#include <glad/gl.h>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

namespace Light {

FailedAssertion::FailedAssertion(const char *file, int line)
{
	lt_log(critical, "Assertion failed in: {} (line {})", file, line);
}

glException::glException(unsigned int source, unsigned int type, unsigned int id, const char *msg)
{
	// #todo: improve
	lt_log(critical, "________________________________________");
	lt_log(critical, "glException::glException::");
	// lt_log(critical, "        Severity: {}",
	// Stringifier::glDebugMsgSeverity(GL_DEBUG_SEVERITY_HIGH));
	lt_log(critical, "        Source  : {}", Stringifier::glDebugMsgSource(source));
	lt_log(critical, "        Type    : {}", Stringifier::glDebugMsgType(type));
	lt_log(critical, "        ID      : {}", id);
	// lt_log(critical, "        Vendor  : {}", glGetString(GL_VENDOR));
	// lt_log(critical, "        renderer: {}", glGetString(GL_RENDERER));
	// lt_log(critical, "        Version : {}", glGetString(GL_VERSION));
	// lt_log(critical, "        critical, SVersion: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
	lt_log(critical, "        {}", msg);
	lt_log(critical, "________________________________________");
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
	lt_log(critical, "________________________________________");
	lt_log(critical, "dxException::dxException::");
	lt_log(critical, "        File: {}, Line: {}", file, line);
	lt_log(critical, "        {}", message);
	lt_log(critical, "________________________________________");

	LocalFree(message);
}
#endif

} // namespace Light
