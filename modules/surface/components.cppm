module;
#ifdef LIGHT_PLATFORM_LINUX
typedef struct _XDisplay Display;
#endif

export module surface.system:components;
import std;
import math.vec2;
import surface.events;
import surface.requests;

namespace lt::surface {

/** Represents a platform's surface (eg. a Window).
 *
 * @note This is a "system component"
 */
export class SurfaceComponent
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
	    MouseMovedEvent,
	    ButtonPressedEvent,
	    ButtonReleasedEvent>;

	using Request = std::variant<
	    ModifyTitleRequest,
	    ModifyResolutionRequest,
	    ModifyPositionRequest,
	    ModifyVisibilityRequest>;

#ifdef LIGHT_PLATFORM_LINUX
	struct NativeData
	{
		Display *display;
		std::uint32_t window;
		unsigned long wm_delete_message;
	};
#endif

	static constexpr auto max_dimension = 4096;

	static constexpr auto max_title_length = 256;

	struct CreateInfo
	{
		std::string_view title;

		math::uvec2 resolution;

		bool vsync;

		bool visible;
	};

	[[nodiscard]] auto get_title() const -> std::string_view
	{
		return m_title;
	}

	[[nodiscard]] auto get_resolution() const -> const math::uvec2 &
	{
		return m_resolution;
	}

	[[nodiscard]] auto get_position() const -> const math::ivec2 &
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

	[[nodiscard]] auto get_native_data() const -> const NativeData &
	{
		return m_native_data;
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
	    , m_native_data({})
	{
	}

	std::string m_title;

	math::uvec2 m_resolution;

	math::ivec2 m_position;

	bool m_vsync;

	bool m_visible;

	NativeData m_native_data;

	std::vector<Event> m_event_queue;

	std::vector<Request> m_requests;
};

} // namespace lt::surface
