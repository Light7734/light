#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/graphics_context.hpp>
#include <glm/glm.hpp>

namespace Light {

class Event;

struct WindowProperties
{
	std::string title;

	glm::uvec2 size;

	bool vsync, visible;
};

class Window
{
public:
	static Scope<Window> create(std::function<void(Event &)> callback);

	Window(): m_graphics_context(nullptr), m_properties {}, b_Closed(false)
	{
	}

	Window(const Window &) = delete;

	Window &operator=(const Window &) = delete;

	virtual ~Window() = default;

	virtual void poll_events() = 0;

	virtual void on_event(const Event &event) = 0;

	virtual void set_properties(
	    const WindowProperties &properties,
	    bool affectVisibility = false
	) = 0;

	virtual void set_title(const std::string &title) = 0;

	/** pass 0 for width or height for single dimension resizing */
	virtual void set_size(const glm::uvec2 &size, bool additive = false) = 0;

	void close()
	{
		b_Closed = true;
	}

	virtual void set_v_sync(bool vsync, bool toggle = false) = 0;

	virtual void set_visibility(bool visible, bool toggle = false) = 0;

	auto get_graphics_context() const -> GraphicsContext *
	{
		return m_graphics_context.get();
	}

	auto get_properties() const -> const WindowProperties &
	{
		return m_properties;
	}

	auto get_title() const -> const std::string &
	{
		return m_properties.title;
	}

	auto get_size() const -> const glm::uvec2 &
	{
		return m_properties.size;
	}

	auto is_closed() const -> bool
	{
		return b_Closed;
	}

	auto is_v_sync() const -> bool
	{
		return m_properties.vsync;
	}

	auto is_visible() const -> bool
	{
		return m_properties.visible;
	}

protected:
	Scope<GraphicsContext> m_graphics_context;

	WindowProperties m_properties;

	bool b_Closed;
};

} // namespace Light
