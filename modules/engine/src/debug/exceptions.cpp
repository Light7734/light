#include <engine/debug/exceptions.hpp>
#include <glad/gl.h>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

namespace lt {

FailedAssertion::FailedAssertion(const char *file, int line)
{
	log_crt("Assertion failed in: {} (line {})", file, line);
}

glException::glException(unsigned int source, unsigned int type, unsigned int id, const char *msg)
{
	// #todo: improve
	log_crt("________________________________________");
	log_crt("glException::glException::");
	// log_crt("        Severity: {}",
	// Stringifier::glDebugMsgSeverity(GL_DEBUG_SEVERITY_HIGH));
	// log_crt("        Source  : {}", Stringifier::glDebugMsgSource(source));
	// log_crt("        Type    : {}", Stringifier::glDebugMsgType(type));
	log_crt("        ID      : {}", id);
	// log_crt("        Vendor  : {}", glGetString(GL_VENDOR));
	// log_crt("        renderer: {}", glGetString(GL_RENDERER));
	// log_crt("        Version : {}", glGetString(GL_VERSION));
	// log_crt("        critical, SVersion: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
	log_crt("        {}", msg);
	log_crt("________________________________________");
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
	log_crt("________________________________________");
	log_crt("dxException::dxException::");
	log_crt("        File: {}, Line: {}", file, line);
	log_crt("        {}", message);
	log_crt("________________________________________");

	LocalFree(message);
}
#endif

} // namespace lt
