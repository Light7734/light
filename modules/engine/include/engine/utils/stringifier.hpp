#pragma once
#ifndef LIGHT_STRINGIFIER_H
	#define LIGHT_STRINGIFIER_H

	#include <engine/base/base.hpp>

namespace Light {

enum class GraphicsAPI;

class Stringifier
{
public:
	static std::string glDebugMsgSeverity(unsigned int severity);
	static std::string glDebugMsgSource(unsigned int source);
	static std::string glDebugMsgType(unsigned int type);

	static std::string spdlogLevel(unsigned int level);

	static std::string GraphicsAPIToString(GraphicsAPI api);
};

} // namespace Light

#endif
