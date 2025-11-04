export module debug.instrumentor;

import std;
import logger;

namespace lt::debug {

struct ScopeProfileResult
{
	std::string name;
	long long start, duration;
	std::uint32_t threadID;
};

class Instrumentor
{
public:
	static auto instance() -> Instrumentor &
	{
		static auto instance = Instrumentor {};
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

	static void submit_scope_profile(const ScopeProfileResult &profileResult)
	{
		instance().submit_scope_profile_impl(profileResult);
	}

private:
	std::ofstream m_output_file_stream;

	unsigned int m_current_session_count { 0u };

	Instrumentor() = default;

	void begin_session_impl(const std::string &outputPath);

	void end_session_impl();

	void submit_scope_profile_impl(const ScopeProfileResult &profileResult);
};

class InstrumentorTimer
{
public:
	InstrumentorTimer(const std::string &scopeName);

	~InstrumentorTimer();

private:
	ScopeProfileResult m_result;

	std::chrono::time_point<std::chrono::steady_clock> m_start;
};

} // namespace lt::debug

/* scope */
#define lt_profile_scope(name)                        lt_profile_scope_no_redifinition(name, __LINE__)
#define lt_profile_scope_no_redifinition(name, line)  lt_profile_scope_no_redifinition2(name, line)
#define lt_profile_scope_no_redifinition2(name, line) InstrumentorTimer timer##line(name)

/* function */
#define LT_PROFILE_FUNCTION lt_profile_scope(__FUNCSIG__)

/* session */
#define lt_profile_begin_session(outputPath) ::lt::Instrumentor::begin_session(outputPath)
#define lt_profile_end_session()             ::lt::Instrumentor::end_session()

module :private;
using namespace lt::debug;

void Instrumentor::begin_session_impl(const std::string &outputPath)
{
	std::filesystem::create_directory(outputPath.substr(0, outputPath.find_last_of('/') + 1));

	m_output_file_stream.open(outputPath);
	m_output_file_stream << "{\"traceEvents\":[";
}

void Instrumentor::end_session_impl()
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

void Instrumentor::submit_scope_profile_impl(const ScopeProfileResult &profileResult)
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

InstrumentorTimer::InstrumentorTimer(const std::string &scopeName)
    : m_result({ .name = scopeName, .start = 0, .duration = 0, .threadID = 0 })
    , m_start(std::chrono::steady_clock::now())
{
}

InstrumentorTimer::~InstrumentorTimer()
{
	auto end = std::chrono::steady_clock::now();

	m_result.start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start)
	                     .time_since_epoch()
	                     .count();

	m_result.duration = std::chrono::time_point_cast<std::chrono::microseconds>(end)
	                        .time_since_epoch()
	                        .count()
	                    - m_result.start;

	Instrumentor::submit_scope_profile(m_result);
}
