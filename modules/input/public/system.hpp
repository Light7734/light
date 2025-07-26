#pragma once

#include <surface/system.hpp>

namespace lt::input {

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};

/**
 *
 * @note If this system is attached, it will always consume the input events f rom surface.
 * Therefore if you want any input detection mechanism, callbacks should be setup with this
 * system and not directly with surface.
 */
class System
{
public:
	System(lt::surface::System &surface_system)
	{
		surface_system.add_event_listener([this](auto &&event) {
			return handle_event(std::forward<decltype(event)>(event));
		});
	};

private:
	auto handle_event(const lt::surface::System::Event &event) -> bool
	{
		const auto visitor = overloads {
			[this](const lt::surface::KeyPressedEvent &event) {
			    m_keys[event.get_key()] = true;
			    return true;
			},

			[](const lt::surface::KeyRepeatEvent &) { return false; },

			[](const lt::surface::KeyReleasedEvent &) { return false; },

			[](const lt::surface::KeySetCharEvent &) { return false; },

			[](const lt::surface::MouseMovedEvent &) { return false; },

			[](const lt::surface::WheelScrolledEvent &) { return false; },

			[](const lt::surface::ButtonPressedEvent &) { return false; },

			[](const lt::surface::ButtonReleasedEvent &) { return false; },

			[](const auto &) { return false; },
		};

		return std::visit(visitor, event);
	}

	void setup_callbacks(GLFWwindow *handle);

	std::array<bool, 512> m_keys {};
};


} // namespace lt::input
