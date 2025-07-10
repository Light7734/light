#pragma once

#define dxc(x) dxc_no_redifinition(x, __LINE__)

#define dxc_no_redifinition(x, line) dxc_no_redifinition2(x, line)

#define dxc_no_redifinition2(x, line) \
	HRESULT hr##line;                 \
	if (FAILED(hr##line = x))         \
	throw dxException(hr##line, __FILE__, line)

namespace Light {

#ifdef LIGHT_PLATFORM_WINDOWS
// DirectX
struct dxException: std::exception
{
	dxException(long hr, const char *file, int line);
};
#endif

} // namespace Light
