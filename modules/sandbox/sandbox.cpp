import preliminary;
import time;
import logger;
import renderer.system;
import renderer.frontend;
import surface.system;
import surface.events;
import surface.requests;
import ecs.entity;
import input.codes;
import ecs.registry;
import memory.scope;
import memory.reference;
import logger;
import math.vec2;
import app.system;

constexpr auto title = "TestWindow";
constexpr auto width = 800u;
constexpr auto height = 600u;
constexpr auto vsync = true;
constexpr auto visible = true;

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};

void renderer_debug_callback(
    lt::renderer::IDebugger::MessageSeverity message_severity,
    lt::renderer::IDebugger::MessageType message_type,
    lt::renderer::IDebugger::MessageData data,
    std::any &user_data
)
{
	ignore = message_severity;
	ignore = message_type;
	ignore = user_data;

	lt::log::trace("< Renderer > ==> {}", std::string { data.message });
}

auto main() -> i32
try
{
	auto registry = lt::memory::create_ref<lt::ecs::Registry>();
	auto surface_system = lt::surface::System { registry };

	auto entity = registry->create_entity();

	lt::log::trace("Creating surface component");
	surface_system.create_surface_component(
	    entity,
	    lt::surface::SurfaceComponent::CreateInfo {
	        .title = title,
	        .position = { 500, 500 },

	        .resolution = { width, height },
	        .vsync = vsync,
	        .visible = visible,
	    }
	);

	auto &window = registry->get<lt::surface::SurfaceComponent>(entity);

	const auto config = lt::renderer::System::Configuration {
		.target_api = lt::renderer::Api::vulkan,
		.max_frames_in_flight = 3u,
	};

	const auto debug_callback_info = lt::renderer::IDebugger::CreateInfo {
		.severities = lt::renderer::IDebugger::MessageSeverity::all,
		.types = lt::renderer::IDebugger::MessageType::all,
		.callback = &renderer_debug_callback,
		.user_data = nullptr,
	};

	const auto surface_entity = lt::ecs::Entity { registry, entity };

	auto renderer_system = lt::renderer::System { lt::renderer::System::CreateInfo {
		config,
		registry,
		surface_entity,
		debug_callback_info,
	} };


	auto should_close = false;
	const auto visitor = overloads {
		[&](const lt::surface::ClosedEvent &) {
		    lt::log::info("Closing due to: Window X button pressed");
		    should_close = true;
		},
		[&](const lt::surface::MovedEvent &event) {
		    lt::log::info("Moved: {}", event.get_position());
		},
		[&](const lt::surface::ResizedEvent &event) {
		    lt::log::info("Resized: {}", event.get_size());
		},
		[&](const lt::surface::LostFocusEvent &) { lt::log::info("Lost focus"); },
		[&](const lt::surface::GainFocusEvent &) { lt::log::info("Gain focus"); },
		[&](const lt::surface::KeyPressedEvent &event) {
		    if (event.get_key() == lt::Key::escape)
		    {
			    lt::log::info("Closing due to: Escape key pressed");
			    should_close = true;
		    }
		    lt::log::info("Key pressed: {}", event.get_key());
		},
		[&](const lt::surface::KeyReleasedEvent &event) {
		    lt::log::info("Key released: {}", event.get_key());
		},
		[&](const lt::surface::PointerEvent &event) {
		    lt::log::info("Pointer: {}", event.get_position());
		}
	};

	while (!should_close)
	{
		surface_system.tick({});
		renderer_system.tick({});

		for (const auto &event : window.peek_events())
		{
			std::visit(visitor, event);
		}
	}
}
catch (const std::exception &exp)
{
	lt::log::critical("Aborting due to uncaught std::exception:");
	lt::log::critical("\twhat: {}", exp.what());
}
catch (...)
{
	lt::log::critical("Aborting due to uncaught non std::exception!");
}
