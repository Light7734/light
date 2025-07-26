#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>

namespace lt::vk {

class Instance
{
public:
	Instance()
	{
	}

private:
	::vk::Instance m_instace;
};

} // namespace lt::vk
