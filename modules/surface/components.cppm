module;

struct wl_display;
struct wl_surface;
struct xdg_surface;
struct xdg_toplevel;

export module surface.system:components;

import preliminary;
import math.vec2;
import surface.events;
import surface.requests;


export namespace lt::surface {

/** Represents a platform's surface (eg. a Window).
 *
 * @note This is a "system component"
 */
class SurfaceComponent
{
public:
	friend class System;

	using Event = std::variant<
	    ClosedEvent,
	    MovedEvent,
	    ResizedEvent,
	    LostFocusEvent,
	    GainFocusEvent,
	    KeyPressedEvent,
	    KeyReleasedEvent,
	    PointerEvent>;

	using Request = std::variant<
	    ModifyTitleRequest,
	    ModifyResolutionRequest,
	    ModifyPositionRequest,
	    ModifyVisibilityRequest>;

	static constexpr auto max_dimension = 4096;

	static constexpr auto max_title_length = 256;

	// TODO(Light): add `center_to_screen` flag
	// TODO(Light): add `screen_mode` flag (windowed/full_screen/windowed_full_screen)
	struct CreateInfo
	{
		std::string title;

		math::vec2_i32 position;

		math::vec2_u32 resolution;

		bool vsync;

		bool visible;
	};

	[[nodiscard]] auto get_title() const -> std::string // yes copy the title, whatever...
	{
		return m_title;
	}

	[[nodiscard]] auto get_resolution() const -> const math::vec2_u32 &
	{
		return m_resolution;
	}

	[[nodiscard]] auto get_position() const -> const math::vec2_i32 &
	{
		return m_position;
	}

	[[nodiscard]] auto is_vsync() const -> bool
	{
		return m_vsync;
	}

	[[nodiscard]] auto is_visible() const -> bool
	{
		return m_visible;
	}

	[[nodiscard]] auto get_wl_display() -> wl_display *
	{
		return m_wl_display;
	}

	[[nodiscard]] auto get_wl_surface() -> wl_surface *
	{
		return m_wl_surface;
	}

	[[nodiscard]] auto get_xdg_surface() -> xdg_surface *
	{
		return m_xdg_surface;
	}

	[[nodiscard]] auto get_xdg_toplevel() -> xdg_toplevel *
	{
		return m_xdg_toplevel;
	}

	[[nodiscard]] auto peek_events() const -> const std::vector<Event> &
	{
		return m_event_queue;
	}

	[[nodiscard]] auto peek_requests() const -> const std::vector<Request> &
	{
		return m_requests;
	};

	void push_request(const Request &request)
	{
		m_requests.emplace_back(request);
	}

	/** @note: Only the surface system and tests should push events */
	void push_event(const Event &event)
	{
		m_event_queue.emplace_back(event);
	}

private:
	SurfaceComponent(const CreateInfo &info)
	    : m_title(info.title)
	    , m_resolution(info.resolution)
	    , m_vsync(info.vsync)
	    , m_visible(info.visible)
	{
	}

	std::string m_title {};

	math::vec2_u32 m_resolution {};

	math::vec2_i32 m_position {};

	bool m_vsync {};

	bool m_visible {};

	wl_display *m_wl_display {};

	wl_surface *m_wl_surface {};

	xdg_surface *m_xdg_surface {};

	xdg_toplevel *m_xdg_toplevel {};

	std::vector<Event> m_event_queue {};

	std::vector<Request> m_requests {};
};

} // namespace lt::surface
