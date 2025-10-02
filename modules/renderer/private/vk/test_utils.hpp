#pragma once

#include <ranges>
#include <renderer/vk/context/context.hpp>
#include <renderer/vk/context/surface.hpp>
#include <renderer/vk/debug/messenger.hpp>
#include <surface/components.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

using ::lt::test::Case;
using ::lt::test::expect_eq;
using ::lt::test::expect_false;
using ::lt::test::expect_not_nullptr;
using ::lt::test::expect_throw;
using ::lt::test::expect_true;
using ::lt::test::Suite;
using ::std::ignore;

namespace constants {

constexpr auto resolution = lt::math::uvec2 { 800u, 600u };

}

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

[[nodiscard]] inline auto create_context()
    -> std::pair<lt::renderer::vk::Context, lt::surface::System>
{
	using lt::surface::SurfaceComponent;

	auto registry = lt::create_ref<lt::ecs::Registry>();
	auto entity = lt::ecs::Entity { registry, registry->create_entity() };
	auto surface_system = lt::surface::System(registry);
	entity.add<SurfaceComponent>(SurfaceComponent::CreateInfo {
	    .title = "",
	    .resolution = constants::resolution,
	});

	return { lt::renderer::vk::Context { entity }, std::move(surface_system) };
}

template<>
struct std::formatter<VkExtent2D>
{
	constexpr auto parse(std::format_parse_context &context)
	{
		return context.begin();
	}

	auto format(const VkExtent2D &val, std::format_context &context) const
	{
		return std::format_to(context.out(), "{}, {}", val.width, val.height);
	}
};

inline auto operator==(VkExtent2D lhs, VkExtent2D rhs) -> bool
{
	return lhs.width == rhs.width && lhs.height == rhs.height;
}
