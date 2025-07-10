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
