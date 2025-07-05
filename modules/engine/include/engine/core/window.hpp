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
protected:
	Scope<GraphicsContext> m_GraphicsContext;
	WindowProperties m_Properties;
	bool b_Closed;

public:
	static Scope<Window> Create(std::function<void(Event &)> callback);

	Window(): m_GraphicsContext(nullptr), m_Properties {}, b_Closed(false)
	{
	}

	Window(const Window &) = delete;
	Window &operator=(const Window &) = delete;

	virtual ~Window() = default;

	/* events */
	virtual void PollEvents() = 0;
	virtual void OnEvent(const Event &event) = 0;

	//======================================== SETTERS ========================================//
	virtual void SetProperties(
	    const WindowProperties &properties,
	    bool affectVisibility = false
	) = 0;

	virtual void SetTitle(const std::string &title) = 0;

	virtual void SetSize(const glm::uvec2 &size, bool additive = false) = 0; // pass 0 for width or
	                                                                         // height for single
	                                                                         // dimension resizing

	inline void Close()
	{
		b_Closed = true;
	}
	virtual void SetVSync(bool vsync, bool toggle = false) = 0;
	virtual void SetVisibility(bool visible, bool toggle = false) = 0;
	//======================================== SETTERS ========================================//

	//============================== GETTERS ==============================//
	inline GraphicsContext *GetGfxContext() const
	{
		return m_GraphicsContext.get();
	}

	inline const WindowProperties &GetProperties() const
	{
		return m_Properties;
	}

	inline const std::string &GetTitle() const
	{
		return m_Properties.title;
	}

	inline const glm::uvec2 &GetSize() const
	{
		return m_Properties.size;
	}

	inline bool IsClosed() const
	{
		return b_Closed;
	}
	inline bool IsVSync() const
	{
		return m_Properties.vsync;
	}
	inline bool IsVisible() const
	{
		return m_Properties.visible;
	}
	//============================== GETTERS ==============================//

protected:
};

} // namespace Light
