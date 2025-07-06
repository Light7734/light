#pragma once
#ifndef LIGHT_STRINGIFIER_H
	#define LIGHT_STRINGIFIER_H

	#include <engine/base/base.hpp>

namespace Light {

enum class GraphicsAPI;

class Stringifier
{
public:
	static auto glDebugMsgSeverity(unsigned int severity) -> std::string;

	static auto glDebugMsgSource(unsigned int source) -> std::string;

	static auto glDebugMsgType(unsigned int type) -> std::string;

	static auto spdlogLevel(unsigned int level) -> std::string;

	static auto graphics_api_to_string(GraphicsAPI api) -> std::string;
};

} // namespace Light

#endif
