#pragma once


#include <glm/glm.hpp>
#include <renderer/graphics_context.hpp>

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
	static Scope<Window> create(const std::function<void(Event &)> &callback);

	Window(): m_properties {}
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

	[[nodiscard]] auto get_properties() const -> const WindowProperties &
	{
		return m_properties;
	}

	[[nodiscard]] auto get_title() const -> const std::string &
	{
		return m_properties.title;
	}

	[[nodiscard]] auto get_size() const -> const glm::uvec2 &
	{
		return m_properties.size;
	}

	[[nodiscard]] auto is_closed() const -> bool
	{
		return b_Closed;
	}

	[[nodiscard]] auto is_v_sync() const -> bool
	{
		return m_properties.vsync;
	}

	[[nodiscard]] auto is_visible() const -> bool
	{
		return m_properties.visible;
	}

	virtual auto get_handle() -> void * = 0;

protected:
	WindowProperties m_properties;

	bool b_Closed { false };
};

} // namespace Light
