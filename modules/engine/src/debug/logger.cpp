#include <engine/debug/logger.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Light {

Logger *Logger::s_Context = nullptr;

Scope<Logger> Logger::Create()
{
	return MakeScope<Logger>(new Logger());
}

Logger::Logger()
    : m_EngineLogger(nullptr)
    , m_FileLogger(nullptr)
    , m_LogFilePath(LT_LOG_FILE_LOCATION)
{
	ASSERT(!s_Context, "An instance of 'Logger' already exists, do not construct this class!");
	s_Context = this;

	// set spdlog pattern
	// create loggers
	spdlog::set_pattern("%^[%H:%M:%S]%g@%! ==> %v%$");
#ifndef LIGHT_DIST
	spdlog::set_pattern("%^[%H:%M:%S]%! ==> %v%$");
	m_EngineLogger = spdlog::stdout_color_mt("Engine");
#endif

	m_FileLogger = spdlog::basic_logger_mt("File", m_LogFilePath);
	m_FileLogger->set_pattern("%^[%M:%S:%e] <%l>: %v%$");

	// set level
#if defined(LIGHT_DEBUG)
	m_EngineLogger->set_level(spdlog::level::trace);
	m_ClientLogger->set_level(spdlog::level::trace);
#elif defined(LIGHT_RELEASE)
	s_EngineLogger->set_level(spdlog::level::info);
	s_ClientLogger->set_level(spdlog::level::info);
#endif
}

void Logger::LogDebugData()
{
	// #todo: improve
	LOG(info, "________________________________________");
	LOG(info, "Logger::");
	LOG(info, "        EngineLevel : {}", Stringifier::spdlogLevel(m_EngineLogger->level()));
	LOG(info, "        FileLevel   : {}", Stringifier::spdlogLevel(m_FileLogger->level()));
	LOG(info, "        DefaultLevel: {}", Stringifier::spdlogLevel(spdlog::get_level()));
	LOG(info, "________________________________________");
}

} // namespace Light
