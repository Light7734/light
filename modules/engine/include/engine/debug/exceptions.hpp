#pragma once

#define DXC(x) DXC_NO_REDIFINITION(x, __LINE__)

#define DXC_NO_REDIFINITION(x, line) DXC_NO_REDIFINITION2(x, line)

#define DXC_NO_REDIFINITION2(x, line) \
	HRESULT hr##line;                 \
	if (FAILED(hr##line = x))         \
	throw dxException(hr##line, __FILE__, line)

namespace Light {

struct FailedAssertion: std::exception
{
	FailedAssertion(const char* file, int line);
};

// OpenGL
struct glException: std::exception
{
	glException(unsigned int source, unsigned int type, unsigned int id, const char* msg);
};

#ifdef LIGHT_PLATFORM_WINDOWS
// DirectX
struct dxException: std::exception
{
	dxException(long hr, const char* file, int line);
};
#endif

} // namespace Light
