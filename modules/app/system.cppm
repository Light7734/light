export module app.system;

import preliminary;
import logger;

export namespace lt::app {

/** Information required to tick a system.
 * @note May be used across an entire application-frame (consisting of multiple systems ticking)
 */
struct TickInfo
{
	/** Timepoint type */
	using Timepoint_T = std::chrono::time_point<std::chrono::steady_clock>;

	/** Duration type */
	using Duration_T = std::chrono::duration<f64>;

	/** Duration since previous tick's end_time to current tick's start_time. */
	Duration_T delta_time {};

	/** Maximum duration the system is expected to finish ticking in.
	 *
	 * - if `end_time - start_time > budget` -> the system exceeded its ticking budget.
	 * - else `end_time - start_time < budget` -> the system ticked properly.
	 *
	 * In other words, `end_time` is expected to be less than `start_time + budget`.
	 *
	 * @note `end_time` comes from TickResult
	 */
	Duration_T budget {};

	/** Exact time when ticking started. */
	Timepoint_T start_time;
};

/** Information about how a system's tick performed */
struct TickResult
{
	/** Timepoint type */
	using Timepoint_T = std::chrono::time_point<std::chrono::steady_clock>;

	/** Duration type */
	using Duration_T = std::chrono::duration<f64>;

	/** The info supplied to the system for ticking. */
	TickInfo info;

	/** Equivalent to `end_time - info.start_time`. */
	Duration_T duration {};

	/** Exact timepoint when ticking ended. */
	Timepoint_T end_time;
};

/** The base, pure-virtual class for creating systems. */
class ISystem
{
public:
	ISystem() = default;

	virtual ~ISystem() = default;

	ISystem(ISystem &&) = default;

	ISystem(const ISystem &) = delete;

	auto operator=(ISystem &&) -> ISystem & = default;

	auto operator=(const ISystem &) -> ISystem & = delete;

	virtual void on_register() = 0;

	virtual void on_unregister() = 0;

	virtual void tick(TickInfo tick) = 0;

	[[nodiscard]] virtual auto get_last_tick_result() const -> const TickResult & = 0;
};

} // namespace lt::app
