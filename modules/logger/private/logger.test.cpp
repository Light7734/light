#include <logger/logger.hpp>
#include <test/test.hpp>

using ::lt::test::Case;
using ::lt::test::Suite;

Suite suite = [] {
	Case { "no format" } = [] {
		lt::log::trace("trace");
		lt::log::debug("debug");
		lt::log::info("info");
		lt::log::warn("warn");
		lt::log::error("error");
		lt::log::critical("critical");
	};

	Case { "formatted" } = [] {
		lt::log::trace("trace {}", 69);
		lt::log::debug("debug {}", 69);
		lt::log::info("info {}", 69);
		lt::log::warn("warn {}", 69);
		lt::log::error("error {}", 69);
		lt::log::critical("critical {}", 69);
	};
};
