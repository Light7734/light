#include <renderer/system.hpp>
#include <renderer/vk/context/context.hpp>
#include <renderer/vk/debug/messenger.hpp>
#include <renderer/vk/renderer/pass.hpp>
#include <renderer/vk/renderer/renderer.hpp>

using ::lt::assets::ShaderAsset;

namespace lt::renderer::vk {
class ValidationObserver
{
	using Messenger = lt::renderer::vk::Messenger;
	using enum Messenger::Type;
	using enum Messenger::Severity;

public:
	ValidationObserver()
	    : m_messenger(
	          Messenger::CreateInfo {
	              .severity = static_cast<Messenger::Severity>(warning | error),
	              .type = lt::renderer::vk::Messenger::all_type,
	              .callback = &callback,
	              .user_data = &m_had_any_messages,
	          }
	      )
	{
	}

	~ValidationObserver()
	{
	}

	[[nodiscard]] auto had_any_messages() const -> bool
	{
		return m_had_any_messages;
	}

private:
	static void callback(
	    Messenger::Severity message_severity,
	    Messenger::Type message_type,
	    Messenger::CallbackData_T vulkan_data,
	    void *user_data
	)
	{
		std::ignore = message_severity;
		std::ignore = message_type;
		for (auto idx = 0; idx < vulkan_data->objectCount; ++idx)
		{
			auto object = vulkan_data->pObjects[idx];
			std::println(
			    "0x{:x}({}) = {}",
			    object.objectHandle,
			    string_VkObjectType(object.objectType),
			    object.pObjectName ? object.pObjectName : "unnamed"
			);
		}

		std::println("Validation message: {}", vulkan_data->pMessage);

		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
		*(bool *)user_data = true;
	}

	Messenger m_messenger;
	bool m_had_any_messages = false;
};
} // namespace lt::renderer::vk


namespace lt::renderer {

System::System(CreateInfo info)
    : m_registry(std::move(info.registry))
    , m_stats(info.system_stats)
    , m_context(create_scope<vk::Context>(info.surface_entity))
{
	m_validation_observer = new vk::ValidationObserver();
	// ensure(m_stats, "Failed to initialize system: null stats");
	ensure(m_registry, "Failed to initialize renderer system: null registry");

	m_pass = create_ref<vk::Pass>(
	    *m_context,
	    ShaderAsset { "./data/test_assets/triangle.vert.asset" },
	    ShaderAsset { "./data/test_assets/triangle.frag.asset" }
	);

	m_renderer = create_scope<vk::Renderer>(*m_context, m_pass);
}

System::~System()
{
}

void System::on_register()
{
}

void System::on_unregister()
{
}

void System::tick(app::TickInfo tick)
{
	if (!m_renderer->draw(m_frame_idx))
	{
		m_context->recreate_swapchain();
		m_renderer->replace_swapchain(m_context->swapchain());
		m_pass->replace_swapchain(m_context->swapchain());
		m_renderer->draw(m_frame_idx);
	}

	m_frame_idx = (m_frame_idx + 1) % vk::Renderer::max_frames_in_flight;
}

} // namespace lt::renderer
