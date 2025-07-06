#include <engine/debug/logger.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

Logger::Logger(): spd_logger(spdlog::stdout_color_mt("Logger"))
{
	spd_logger->set_pattern("%^%v%$");
	spd_logger->set_level(spdlog::level::level_enum::trace);
}

Logger::~Logger()
{
	spdlog::drop_all();
}

auto Logger::instance() -> Logger &
{
	static auto logger = Logger {};
	return logger;
}
