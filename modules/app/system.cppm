export module app.system;
import logger;
import std;

namespace lt::app {

/** Information required to tick a system.
 * @note May be used across an entire application-frame (consisting of multiple systems ticking)
 */
export struct TickInfo
{
	using Timepoint_T = std::chrono::time_point<std::chrono::steady_clock>;

	using Duration_T = std::chrono::duration<double>;

	/** Duration since previous tick's end_time to current tick's start_time. */
	Duration_T delta_time {};

	/** Maximum duration the system is expected to finish ticking in.
	 *
	 * if end_time - start_time > budget -> the system exceeded its ticking budget.
	 * else end_time - start_time < budget -> the system ticked properly.
	 *
	 * In other words, end_time is expected to be less than start_time + budget.
	 */
	Duration_T budget {};

	/** Exact time which ticking started. */
	Timepoint_T start_time;
};

/** Information about how a system's tick performed */
export struct TickResult
{
	using Timepoint_T = std::chrono::time_point<std::chrono::steady_clock>;

	using Duration_T = std::chrono::duration<double>;

	/** The info supplied to the system for ticking. */
	TickInfo info;

	/** Equivalent to end_time - info.start_time. */
	Duration_T duration {};

	/** Exact time which ticking ended. */
	Timepoint_T end_time;
};

export struct SystemDiagnosis
{
	enum class Severity : std::uint8_t
	{
		verbose,
		info,
		warning,
		error,
		fatal,
	};

	std::string message;

	std::string code;

	Severity severity;
};

export class SystemStats
{
public:
	void push_diagnosis(SystemDiagnosis &&diagnosis)
	{
		auto diag = m_diagnosis.emplace_back(std::move(diagnosis));

		log::debug("message: {}", diag.message);
	}

	[[nodiscard]] auto empty_diagnosis() const -> bool
	{
		return m_diagnosis.empty();
	}

private:
	std::vector<SystemDiagnosis> m_diagnosis;
};

export class ISystem
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
