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

	virtual void set_size(const glm::uvec2 &size, bool additive = false) = 0; // pass 0 for width or
	                                                                          // height for single
	                                                                          // dimension resizing

	inline void close()
	{
		b_Closed = true;
	}
	virtual void set_v_sync(bool vsync, bool toggle = false) = 0;

	virtual void set_visibility(bool visible, bool toggle = false) = 0;

	inline GraphicsContext *GetGfxContext() const
	{
		return m_graphics_context.get();
	}

	inline const WindowProperties &GetProperties() const
	{
		return m_properties;
	}

	inline const std::string &GetTitle() const
	{
		return m_properties.title;
	}

	inline const glm::uvec2 &get_size() const
	{
		return m_properties.size;
	}

	inline bool is_closed() const
	{
		return b_Closed;
	}
	inline bool is_v_sync() const
	{
		return m_properties.vsync;
	}
	inline bool is_visible() const
	{
		return m_properties.visible;
	}

protected:
	Scope<GraphicsContext> m_graphics_context;

	WindowProperties m_properties;

	bool b_Closed;
};

} // namespace Light
