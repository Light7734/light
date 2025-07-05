#include <engine/debug/instrumentor.hpp>

namespace Light {

Instrumentor *Instrumentor::s_Context = nullptr;

Scope<Instrumentor> Instrumentor::Create()
{
	return MakeScope<Instrumentor>(new Instrumentor);
}

Instrumentor::Instrumentor(): m_current_session_count(0u)
{
	// #todo: maintenance
	ASSERT(
	    !s_Context,
	    "An instance of 'Instrumentor' already exists, do not construct this class!"
	);
	s_Context = this;
}

void Instrumentor::BeginSessionImpl(const std::string &outputPath)
{
	std::filesystem::create_directory(outputPath.substr(0, outputPath.find_last_of('/') + 1));

	m_output_file_stream.open(outputPath);
	m_output_file_stream << "{\"traceEvents\":[";
}

void Instrumentor::EndSessionImpl()
{
	if (m_current_session_count == 0u)
		LOG(warn, "0 profiling for the ended session");

	m_current_session_count = 0u;

	m_output_file_stream << "]}";
	m_output_file_stream.flush();
	m_output_file_stream.close();
}

void Instrumentor::SubmitScopeProfileImpl(const ScopeProfileResult &profileResult)
{
	if (m_current_session_count++ == 0u)
		m_output_file_stream << "{";
	else
		m_output_file_stream << ",{";

	m_output_file_stream << "\"name\":\"" << profileResult.name << "\",";
	m_output_file_stream << "\"cat\": \"scope\",";
	m_output_file_stream << "\"ph\": \"X\",";
	m_output_file_stream << "\"ts\":" << profileResult.start << ",";
	m_output_file_stream << "\"dur\":" << profileResult.duration << ",";
	m_output_file_stream << "\"pid\":0,";
	m_output_file_stream << "\"tid\":" << profileResult.threadID << "";
	m_output_file_stream << "}";
}

InstrumentorTimer::InstrumentorTimer(const std::string &scopeName)
    : m_result({ scopeName, 0, 0, 0 })
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

	Instrumentor::SubmitScopeProfile(m_result);
}

} // namespace Light
