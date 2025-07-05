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

// #todo: add event categories
// #todo: use ofstream in a separate thread
class Instrumentor /* singleton */
{
private:
	static Instrumentor *s_Context;

private:
	std::ofstream m_output_file_stream;

	unsigned int m_current_session_count;

public:
	static Scope<Instrumentor> Create();

	static inline void BeginSession(const std::string &outputPath)
	{
		s_Context->BeginSessionImpl(outputPath);
	}
	static inline void EndSession()
	{
		s_Context->EndSessionImpl();
	}

	static inline void SubmitScopeProfile(const ScopeProfileResult &profileResult)
	{
		s_Context->SubmitScopeProfileImpl(profileResult);
	}

private:
	Instrumentor();

	void BeginSessionImpl(const std::string &outputPath);
	void EndSessionImpl();

	void SubmitScopeProfileImpl(const ScopeProfileResult &profileResult);
};

class InstrumentorTimer
{
private:
	ScopeProfileResult m_result;
	std::chrono::time_point<std::chrono::steady_clock> m_start;

public:
	InstrumentorTimer(const std::string &scopeName);
	~InstrumentorTimer();
};

} // namespace Light

/* scope */
#define LT_PROFILE_SCOPE(name)                        LT_PROFILE_SCOPE_NO_REDIFINITION(name, __LINE__)
#define LT_PROFILE_SCOPE_NO_REDIFINITION(name, line)  LT_PROFILE_SCOPE_NO_REDIFINITION2(name, line)
#define LT_PROFILE_SCOPE_NO_REDIFINITION2(name, line) InstrumentorTimer timer##line(name)

/* function */
#define LT_PROFILE_FUNCTION LT_PROFILE_SCOPE(__FUNCSIG__)

/* session */
#define LT_PROFILE_BEGIN_SESSION(outputPath) ::Light::Instrumentor::BeginSession(outputPath)
#define LT_PROFILE_END_SESSION()             ::Light::Instrumentor::EndSession()
