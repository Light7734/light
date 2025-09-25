#include <renderer/vk/pipeline.hpp>

namespace lt::renderer::vk {

Pipeline::Pipeline(CreateInfo info): m_context(std::move(info.context))
{
	ensure(m_context, "Failed to create vk pipeline: null context");
}

Pipeline::~Pipeline()
{
	if (m_context)
	{
		return;
	}
}

} // namespace lt::renderer::vk
