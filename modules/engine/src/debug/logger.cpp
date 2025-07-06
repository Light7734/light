#include <engine/debug/logger.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Light {

logger *logger::s_context = nullptr;

auto logger::create() -> Scope<logger>
{
	return make_scope<logger>(new logger());
}

logger::logger()
    : m_engine_logger(nullptr)
    , m_file_logger(nullptr)
    , m_log_file_path(LT_LOG_FILE_LOCATION)
{
	lt_assert(!s_context, "An instance of 'logger' already exists, do not construct this class!");
	s_context = this;

	// set spdlog pattern
	// create loggers
	spdlog::set_pattern("%^[%H:%M:%S]%g@%! ==> %v%$");
#ifndef LIGHT_DIST
	spdlog::set_pattern("%^[%H:%M:%S]%! ==> %v%$");
	m_engine_logger = spdlog::stdout_color_mt("Engine");
#endif

	m_file_logger = spdlog::basic_logger_mt("File", m_log_file_path);
	m_file_logger->set_pattern("%^[%M:%S:%e] <%l>: %v%$");

	// set level
#if defined(LIGHT_DEBUG)
	m_engine_logger->set_level(spdlog::level::trace);
	m_client_logger->set_level(spdlog::level::trace);
#elif defined(LIGHT_RELEASE)
	s_EngineLogger->set_level(spdlog::level::info);
	s_ClientLogger->set_level(spdlog::level::info);
#endif
}

void logger::log_debug_data()
{
	// #todo: improve
	lt_log(info, "________________________________________");
	lt_log(info, "logger::");
	lt_log(info, "        EngineLevel : {}", Stringifier::spdlogLevel(m_engine_logger->level()));
	lt_log(info, "        FileLevel   : {}", Stringifier::spdlogLevel(m_file_logger->level()));
	lt_log(info, "        DefaultLevel: {}", Stringifier::spdlogLevel(spdlog::get_level()));
	lt_log(info, "________________________________________");
}

} // namespace Light
