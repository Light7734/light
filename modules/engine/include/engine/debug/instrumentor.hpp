#pragma once

#include <chrono>
#include <engine/base/base.hpp>
#include <fstream>

namespace Light {

struct ScopeProfileResult
{
	std::string name;
	long long start, duration;
	uint32_t threadID;
};

class Instrumentor
{
public:
	static Scope<Instrumentor> create();

	static void begin_session(const std::string &outputPath)
	{
		s_context->begin_session_impl(outputPath);
	}
	static void end_session()
	{
		s_context->end_session_impl();
	}

	static void submit_scope_profile(const ScopeProfileResult &profileResult)
	{
		s_context->submit_scope_profile_impl(profileResult);
	}

private:
	static Instrumentor *s_context;

	std::ofstream m_output_file_stream;

	unsigned int m_current_session_count{0u};

	Instrumentor();

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

} // namespace Light

/* scope */
#define lt_profile_scope(name)                        lt_profile_scope_no_redifinition(name, __LINE__)
#define lt_profile_scope_no_redifinition(name, line)  lt_profile_scope_no_redifinition2(name, line)
#define lt_profile_scope_no_redifinition2(name, line) InstrumentorTimer timer##line(name)

/* function */
#define LT_PROFILE_FUNCTION lt_profile_scope(__FUNCSIG__)

/* session */
#define lt_profile_begin_session(outputPath) ::Light::Instrumentor::begin_session(outputPath)
#define lt_profile_end_session()             ::Light::Instrumentor::end_session()
