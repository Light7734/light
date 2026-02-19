// @todo(Light): Implement...

export module debug.instrumentor;

import preliminary;
import logger;

namespace lt::tracer {

struct ScopeTraceResult
{
	std::string name;
	u64 start, duration;
	u32 threadID;
};

class Tracer
{
public:
	static auto instance() -> Tracer &
	{
		static auto instance = Tracer {};
		return instance;
	}

	static void begin_session(const std::string &outputPath)
	{
		instance().begin_session_impl(outputPath);
	}
	static void end_session()
	{
		instance().end_session_impl();
	}

	static void submit_scope_profile(const ScopeTraceResult &profileResult)
	{
		instance().submit_scope_profile_impl(profileResult);
	}

private:
	std::ofstream m_output_file_stream;

	unsigned int m_current_session_count { 0u };

	Tracer() = default;

	void begin_session_impl(const std::string &outputPath);

	void end_session_impl();

	void submit_scope_profile_impl(const ScopeTraceResult &profileResult);
};

class TracerTimer
{
public:
	TracerTimer(const std::string &scopeName);

	~TracerTimer();

private:
	ScopeTraceResult m_result;

	std::chrono::time_point<std::chrono::steady_clock> m_start;
};

} // namespace lt::tracer

/* scope */
#define lt_trace_scope(name)                        lt_profile_scope_no_redifinition(name, __LINE__)
#define lt_trace_scope_no_redifinition(name, line)  lt_profile_scope_no_redifinition2(name, line)
#define lt_trace_scope_no_redifinition2(name, line) InstrumentorTimer timer##line(name)

/* function */
#define lt_trace_function lt_profile_scope(__FUNCSIG__)

/* session */
#define lt_trace_begin_session(outputPath) ::lt::Instrumentor::begin_session(outputPath)
#define lt_trace_end_session()             ::lt::Instrumentor::end_session()

/** @todo(Light): unimplemented in gcc -- is it even right to use a private fragment? */
// module :private;
namespace lt::tracer {

void Tracer::begin_session_impl(const std::string &outputPath)
{
	std::filesystem::create_directory(outputPath.substr(0, outputPath.find_last_of('/') + 1));

	m_output_file_stream.open(outputPath);
	m_output_file_stream << "{\"traceEvents\":[";
}

void Tracer::end_session_impl()
{
	if (m_current_session_count == 0u)
	{
		log::warn("0 profiling for the ended session");
	}

	m_current_session_count = 0u;

	m_output_file_stream << "]}";
	m_output_file_stream.flush();
	m_output_file_stream.close();
}

void Tracer::submit_scope_profile_impl(const ScopeTraceResult &profileResult)
{
	if (m_current_session_count++ == 0u)
	{
		m_output_file_stream << "{";
	}
	else
	{
		m_output_file_stream << ",{";
	}

	m_output_file_stream << R"("name":")" << profileResult.name << "\",";
	m_output_file_stream << R"("cat": "scope",)";
	m_output_file_stream << R"("ph": "X",)";
	m_output_file_stream << "\"ts\":" << profileResult.start << ",";
	m_output_file_stream << "\"dur\":" << profileResult.duration << ",";
	m_output_file_stream << "\"pid\":0,";
	m_output_file_stream << "\"tid\":" << profileResult.threadID << "";
	m_output_file_stream << "}";
}

TracerTimer::TracerTimer(const std::string &scopeName)
    : m_result({ .name = scopeName, .start = 0, .duration = 0, .threadID = 0 })
    , m_start(std::chrono::steady_clock::now())
{
}

TracerTimer::~TracerTimer()
{
	auto end = std::chrono::steady_clock::now();

	m_result.start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start)
	                     .time_since_epoch()
	                     .count();

	m_result.duration = std::chrono::time_point_cast<std::chrono::microseconds>(end)
	                        .time_since_epoch()
	                        .count()
	                    - m_result.start;

	Tracer::submit_scope_profile(m_result);
}
} // namespace lt::tracer
