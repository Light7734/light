#pragma once

#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/vk/context/context.hpp>

namespace lt::renderer::vk {

class Pipeline
{
public:
	struct CreateInfo
	{
		Ref<Context> context;
	};

	Pipeline(CreateInfo info);

	~Pipeline();

	Pipeline(Pipeline &&) = default;

	Pipeline(const Pipeline &) = delete;

	auto operator=(Pipeline &&) -> Pipeline & = default;

	auto operator=(const Pipeline &) -> Pipeline & = delete;

private:
	VkPipeline m_pipeline = {};

	VkPipelineLayout m_pipeline_layout = {};

	Ref<Context> m_context;
};

}; // namespace lt::renderer::vk
